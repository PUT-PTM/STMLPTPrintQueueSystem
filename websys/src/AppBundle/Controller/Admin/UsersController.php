<?php

namespace AppBundle\Controller\Admin;

use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;

class UsersController extends Controller
{
    /**
     * @Route("/users")
     */
    public function showAction()
    {
        $em = $this->getDoctrine()->getManager();
        $users = $em->getRepository('AppBundle:User')->findAll();

        return $this->render('admin/users.html.twig', array('users' => $users));
    }

    /**
     * @Route("/users/lock/{id}")
     */
    public function lockAction($id)
    {
        if ($id == $this->getUser()->getId()) {
            $this->addFlash('error', 'You cannot lock yourself!');
        } else {
            $userManager = $this->get('fos_user.user_manager');
            $user = $userManager->findUserBy(array('id'=>$id));

            $user->setLocked(true);

            $userManager->updateUser($user);

            $this->addFlash('notice', 'User ' . $user->getUsername() . ' has been locked!');
        }
        return $this->redirectToRoute('app_admin_users_show');
    }

    /**
     * @Route("/users/unlock/{id}")
     */
    public function unlockAction($id)
    {
        $userManager = $this->get('fos_user.user_manager');
        $user = $userManager->findUserBy(array('id'=>$id));

        $user->setLocked(false);

        $userManager->updateUser($user);

        $this->addFlash('notice', 'User ' . $user->getUsername() . ' has been unlocked!');
        return $this->redirectToRoute('app_admin_users_show');
    }
}
