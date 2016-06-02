<?php

namespace AppBundle\Controller\Admin;

use AppBundle\Entity\Position;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Method;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Form\Extension\Core\Type\TextType;
use Symfony\Component\Form\Extension\Core\Type\SubmitType;

class PositionsController extends Controller
{
    /**
     * @Route("/positions")
     * @Method({"GET"})
     */
    public function showAction()
    {
        $em = $this->getDoctrine()->getManager();

        $positions = $em->getRepository('AppBundle:Position')->findAll();

        return $this->render('admin/positions.html.twig', array('positions' => $positions));
    }

    /**
     * @Route("/positions/add")
     * @Method({"GET", "POST"})
     */
    public function addAction(Request $request)
    {
        $em = $this->getDoctrine()->getManager();
        $position = new Position();

        $form = $this->getFormForPosition($position);

        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $em->persist($position);
            $em->flush();

            $this->addFlash('notice', 'Saved new position with id ' . $position->getId() . '!');
            return $this->redirectToRoute('app_admin_positions_show');
        }

        return $this->render('admin/category_new.html.twig', array('form' => $form->createView()));
    }

    /**
     * @Route("/positions/edit/{id}")
     * @Method({"GET", "POST"})
     */
    public function editAction(Request $request, $id)
    {
        $em = $this->getDoctrine()->getManager();
        $position = $em->getRepository('AppBundle:Position')->findOneById($id);
        if (!$position) {
            throw $this->createNotFoundException('No position found for id: ' . $id);
        }

        $form = $this->getFormForPosition($position, true);

        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $em->persist($position);
            $em->flush();

            $this->addFlash('notice', 'Edited position with id ' . $position->getId() . '!');
            return $this->redirectToRoute('app_admin_positions_show');
        }

        return $this->render('admin/category_edit.html.twig', array('form' => $form->createView()));
    }

    private function getFormForPosition(Position $position, $edit = false)
    {
        $formBuilder = $this->createFormBuilder($position)
               ->add('name', TextType::class)
               ->add('save', SubmitType::class, array('label' => 'Save'));
        return $formBuilder->getForm();
    }
}
