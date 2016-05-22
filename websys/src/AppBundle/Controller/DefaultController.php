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
        if(!$this->getUser()->getPosition()) {
            return $this->redirectToRoute('position_selector');
        }
        $curNum = $this->getCurrentPetitioner();
        return $this->render('default/index.html.twig', array('curNum' => $curNum));
    }

    /**
     * @Route("/position", name="position_selector")
     */
    public function positionAction(Request $request)
    {
        $em = $this->getDoctrine()->getManager();
        $pos = $request->request->get('position');
        if($pos != null) {
            $position = $em->getRepository('AppBundle:Position')->find($pos);
            $position->setAssignedUser($this->getUser());
            $em->flush();
            return $this->redirectToRoute('homepage');
        }
        $positions = $em->getRepository('AppBundle:Position')->findByAssignedUser(null);
        return $this->render('default/positionSelector.html.twig', array('positions' => $positions));
    }

    /**
     * @Route("/start", name="start_case")
     */
    public function startCaseAction()
    {
        $em = $this->getDoctrine()->getManager();
        $curNum = $this->getCurrentPetitioner();
        if($curNum != null) {
            $this->addFlash('error', 'Unable to start new case! Please close current case first.');
        } else {
            try {
                $numberToProcess = $em->getRepository('AppBundle:PetitionerNumber')->getOldestNewCase();

                // Fetch "In Progress Status" object from database.
                $status = $em->getRepository('AppBundle:Status')
                        ->getInProgressStatus();

                $numberToProcess->setStatus($status)
                                ->setAssignedUser($this->getUser())
                                ->setPosition($this->getUser()->getPosition())
                                ->setUpdatedOn(new \DateTime('now'));

                $em->flush();

                $this->addFlash('notice', 'Next case started successfully!');
            } catch (\Doctrine\ORM\NoResultException $e) {
                $this->addFlash('error', 'No one is in the queue. Please try again later.');
            }
        }
        return $this->redirectToRoute('homepage');
    }

    /**
     * @Route("/end", name="end_case")
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
                    ->getEndStatus();

            $numberToClose->setStatus($status)
                 ->setUpdatedOn(new \DateTime('now'));

            $em->flush(); // Commit operation on database

            $this->addFlash('notice', 'Petitioner case closed successfully!');
        }
        return $this->redirectToRoute('homepage');
    }
    
    /**
     * @Route("/admin/", name="admin_home")
     */
    public function adminAction()
    {
        $em = $this->getDoctrine()->getManager();

        $statuses = $em->createQuery('SELECT s FROM AppBundle:Status s WHERE s.name != \'End\'')->getResult();
        $currentNumbers = $em->getRepository('AppBundle:PetitionerNumber')
                ->findBy(array('status' => $statuses), array('createdOn' => 'ASC'));

        return $this->render('admin/index.html.twig', array('currentNumbers' => $currentNumbers));
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
