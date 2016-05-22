<?php

namespace AppBundle\Controller\Admin;

use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;

class PositionsController extends Controller
{
    /**
     * @Route("/positions")
     */
    public function showAction()
    {
        $em = $this->getDoctrine()->getManager();

        $positions = $em->getRepository('AppBundle:Position')->findAll();

        return $this->render('admin/positions.html.twig', array('positions' => $positions));
    }
}
