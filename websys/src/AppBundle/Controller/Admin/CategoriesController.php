<?php

namespace AppBundle\Controller\Admin;

use AppBundle\Entity\CaseCategory;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Form\Extension\Core\Type\TextType;
use Symfony\Component\Form\Extension\Core\Type\SubmitType;

class CategoriesController extends Controller
{
    /**
     * @Route("/categories")
     */
    public function showAction()
    {
        $em = $this->getDoctrine()->getManager();
        $categories = $em->getRepository('AppBundle:CaseCategory')->findAll();

        return $this->render('admin/categories.html.twig', array('categories' => $categories));
    }

    /**
     * @Route("/categories/add")
     */
    public function addAction(Request $request)
    {
        $em = $this->getDoctrine()->getManager();
        $category = new CaseCategory();

        $form = $this->getFormForCategory($category);

        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $em->persist($category);
            $em->flush();

            $this->addFlash('notice', 'Saved new category with id ' . $category->getId() . '!');
            return $this->redirectToRoute('app_admin_categories_show');
        }

        return $this->render('admin/category_new.html.twig', array('form' => $form->createView()));
    }

    /**
     * @Route("/categories/edit/{id}")
     */
    public function editAction(Request $request, $id)
    {
        $em = $this->getDoctrine()->getManager();
        $category = $em->getRepository('AppBundle:CaseCategory')->findOneById($id);
        if (!$category) {
            throw $this->createNotFoundException('No category found for id: ' . $id);
        }

        $form = $this->getFormForCategory($category);

        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $em->persist($category);
            $em->flush();

            $this->addFlash('notice', 'Edited category with id ' . $category->getId() . '!');
            return $this->redirectToRoute('app_admin_categories_show');
        }

        return $this->render('admin/category_edit.html.twig', array('form' => $form->createView()));
    }

    private function getFormForCategory(CaseCategory $category)
    {
        return $this->createFormBuilder($category)
               ->add('name', TextType::class)
               ->add('shortcut', TextType::class)
               ->add('save', SubmitType::class, array('label' => 'Save'))
               ->getForm();
    }
}
