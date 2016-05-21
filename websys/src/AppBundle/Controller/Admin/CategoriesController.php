<?php

namespace AppBundle\Controller\Admin;

use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;

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
}
