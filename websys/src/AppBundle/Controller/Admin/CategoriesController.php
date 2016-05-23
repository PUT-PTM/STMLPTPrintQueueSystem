<?php

namespace AppBundle\Controller\Admin;

use AppBundle\Entity\CaseCategory;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Form\Extension\Core\Type\TextType;
use Symfony\Component\Form\Extension\Core\Type\SubmitType;
use Symfony\Component\Form\Extension\Core\Type\CheckboxType;

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
            $category->setActive(true);
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

        $form = $this->getFormForCategory($category, true);

        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $em->persist($category);
            $em->flush();

            $this->addFlash('notice', 'Edited category with id ' . $category->getId() . '!');
            return $this->redirectToRoute('app_admin_categories_show');
        }

        return $this->render('admin/category_edit.html.twig', array('form' => $form->createView()));
    }

    /**
     * @Route("/categories/activate/{id}")
     */
    public function activateAction($id)
    {
        $em = $this->getDoctrine()->getManager();
        $category = $em->getRepository('AppBundle:CaseCategory')->findOneById($id);
        if (!$category) {
            throw $this->createNotFoundException('No category found for id: ' . $id);
        }
        if ($category->getActive()) {
            $this->addFlash('error', 'Category "' . $category->getName() . '" is already activated!');
        } else {
            $category->setActive(true);
        }
        $em->flush();
        $this->addFlash('notice', 'Category "' . $category->getName() . '" activated sucessfully!');
        return $this->redirectToRoute('app_admin_categories_show');
    }

    /**
     * @Route("/categories/deactivate/{id}")
     */
    public function deactivateAction($id)
    {
        $em = $this->getDoctrine()->getManager();
        $category = $em->getRepository('AppBundle:CaseCategory')->findOneById($id);
        if (!$category) {
            throw $this->createNotFoundException('No category found for id: ' . $id);
        }
        if (!$category->getActive()) {
            $this->addFlash('error', 'Category "' . $category->getName() . '" is already deactivated!');
        } else {
            $category->setActive(false);
        }
        $em->flush();
        $this->addFlash('notice', 'Category "' . $category->getName() . '" deactivated sucessfully!');
        return $this->redirectToRoute('app_admin_categories_show');
    }

    private function getFormForCategory(CaseCategory $category, $edit = false)
    {
        $formBuilder = $this->createFormBuilder($category)
               ->add('name', TextType::class)
               ->add('shortcut', TextType::class);
        if ($edit) {
            $formBuilder = $formBuilder->add('active', CheckboxType::class, array(
                'required' => false,
            ));
        }
        $formBuilder = $formBuilder->add('save', SubmitType::class, array('label' => 'Save'));
        return $formBuilder->getForm();
    }
}
