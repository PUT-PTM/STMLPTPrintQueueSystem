<?php

namespace AppBundle\Controller;

use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Symfony\Component\HttpFoundation\Request;

class DefaultController extends Controller
{
    /**
     * @Route("/", name="homepage")
     */
    public function indexAction(Request $request)
    {
        $curNum = $this->getCurrentPetitioner();

        return $this->render('default/index.html.twig', array('curNum' => $curNum));
    }

    private function getCurrentPetitioner()
    {
        $uid = $this->getUser()->getId();
        $em = $this->getDoctrine()->getManager();
        $query = $em->createQuery(
            'SELECT p.generatedNum
             FROM AppBundle:PetitionerNumber p
             JOIN p.status s
             JOIN p.assignedUser u
             WHERE s.name = \'In Progress\'
             AND u.id = :user'
        )->setParameter('user', $uid);

        try {
            return $query->getSingleResult();
        } catch (\Doctrine\ORM\NoResultException $e) {
            return null;
        }
    }
}
