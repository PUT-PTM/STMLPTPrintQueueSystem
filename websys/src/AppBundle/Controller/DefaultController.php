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
    public function indexAction()
    {
        $curNum = $this->getCurrentPetitioner();

        return $this->render('default/index.html.twig', array('curNum' => $curNum));
    }

    /**
     * @Route("/end", name="end_visit")
     */
    public function endCaseAction()
    {
        $curNum = $this->getCurrentPetitioner();
        if($curNum == null) {
            $this->addFlash('error', 'Unable to close case! Reason: there is no "number" in progress.');
        } else {
            $em = $this->getDoctrine()->getManager();

            $numberToClose = $em->getRepository('AppBundle:PetitionerNumber')
                    ->find($curNum['id']);

            // Fetch "End Status" object from database.
            $status = $em->getRepository('AppBundle:Status')
                    ->getEndStatus($curNum['id']);

            $numberToClose->setStatus($status)
                 ->setUpdatedOn(new \DateTime('now'));

            $em->flush(); // Commit operation on database

            $this->addFlash('notice', 'Petitioner case closed successfully!');
        }
        return $this->redirectToRoute('homepage');
    }

    private function getCurrentPetitioner()
    {
        $uid = $this->getUser()->getId();
        $em = $this->getDoctrine()->getManager();
        $query = $em->createQuery(
            'SELECT p.id, p.generatedNum
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
