<?php

namespace AppBundle\Controller;

use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Symfony\Component\HttpFoundation\Request;

class CaseCategoriesController extends Controller
{
    /**
     * @Route("/casecat")
     */
    public function listAction(Request $request)
    {
        $caseCategories = $this->getDoctrine()
                ->getRepository('AppBundle:CaseCategory')
                ->findAll();
        return $this->render('default/casecat.html.twig', [
            'categories' => $caseCategories,
        ]);
    }
}
