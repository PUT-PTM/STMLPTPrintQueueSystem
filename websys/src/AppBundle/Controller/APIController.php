<?php

namespace AppBundle\Controller;

use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Method;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Symfony\Component\HttpFoundation\JsonResponse;

use AppBundle\Entity\CaseCategory;
use AppBundle\Entity\PetitionerNumber;

class APIController extends Controller {
    /**
     * @Route("/api/current")
     * @Method({"GET"})
     */
    public function currentNumbersAction() {
        $em = $this->getDoctrine()->getManager();
        $query = $em->createQuery(<<<QRY
            SELECT pn.generatedNum, p.name, pn.updatedOn
            FROM AppBundle:PetitionerNumber pn
            JOIN pn.position p
            JOIN pn.status s
            WHERE s.name = 'In Progress'
            ORDER BY pn.createdOn DESC
QRY
        );
        return new JsonResponse($query->getResult());
    }

    /**
     * @Route("/api/number/{catId}/")
     * @Method({"GET"})
     */
    public function getNextNumberAction($catId) {
        $em = $this->getDoctrine()->getManager();
        $category = $em->getRepository('AppBundle:CaseCategory')->find($catId);
        $prevNumber = $em->getrepository('AppBundle:PetitionerNumber')
                ->findBy(array(
                    'caseCategory' => $category,
                ), array('createdOn' => 'DESC'));
        $today = new \DateTime('today');
        // If this kind of number exists and it comes from today
        if($prevNumber && $prevNumber[0]->getCreatedOn() > $today) {
            $nextNumber = $this->generateNextPetitionerNumber($prevNumber[0]);
            $em->persist($nextNumber);
            $em->flush();
            return new JsonResponse(array('number' => $nextNumber->getGeneratedNum()));
        } else { // No number found or not assigned today yet
            $newNumber = $this->generateNewPetitionerNumber($category);
            $em->persist($newNumber);
            $em->flush();
            return new JsonResponse(array('number' => $newNumber->getGeneratedNum()));
        }
    }

    /**
     * @Route("/api/camount")
     * @Method({"GET"})
     */
    public function getCategoriesAmount() {
        $em = $this->getDoctrine()->getManager();

        $query = $em->createQueryBuilder()
            ->select('COUNT(c.id)')
            ->from('AppBundle:CaseCategory', 'c')
            ->getQuery();
        $total = $query->getSingleScalarResult();

        return new JsonResponse(array('amount' => (int)$total));
    }

    private function generateNewPetitionerNumber(CaseCategory $category) {
        $em = $this->getDoctrine()->getManager();
        $status = $em->getRepository('AppBundle:Status')->getNewStatus();

        $ret = new PetitionerNumber();
        $ret->setCaseCategory($category);
        $ret->setGeneratedNum($category->getShortcut() . '-001');
        $ret->setCreatedOn(new \DateTime());
        $ret->setStatus($status);

        return $ret;
    }

    private function generateNextPetitionerNumber(PetitionerNumber $old) {
        $em = $this->getDoctrine()->getManager();
        $status = $em->getRepository('AppBundle:Status')->getNewStatus();

        $ret = new PetitionerNumber();
        $ret->setCaseCategory($old->getCaseCategory());

        // extract shortcut from number
        $numSplitted = preg_split('/-/', $old->getGeneratedNum());
        $num = $numSplitted[1]+1;

        $ret->setGeneratedNum($numSplitted[0] . '-' . sprintf('%03d', $num));
        $ret->setCreatedOn(new \DateTime());
        $ret->setStatus($status);

        return $ret;
    }
}
