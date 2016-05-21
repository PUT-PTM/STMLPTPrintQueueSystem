<?php

namespace AppBundle\Controller\Admin;

use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Form\Extension\Core\Type\TextType;
use Symfony\Component\Form\Extension\Core\Type\EmailType;
use Symfony\Component\Form\Extension\Core\Type\PasswordType;
use Symfony\Component\Form\Extension\Core\Type\SubmitType;

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

    /**
     * @Route("/users/new")
     */
    public function newAction(Request $request)
    {
        $userManager = $this->get('fos_user.user_manager');
        $user = $userManager->createUser();

        $form = $this->createFormBuilder($user)
               ->add('username', TextType::class)
               ->add('email', EmailType::class)
               ->add('plainPassword', PasswordType::class)
               ->add('save', SubmitType::class, array('label' => 'Save'))
               ->getForm();

        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $user->setEnabled(true);
            $userManager->updateUser($user);
            $this->addFlash('notice', 'Saved new category with id ' . $user->getId() . '!');
            return $this->redirectToRoute('app_admin_users_show');
        }

        return $this->render('admin/user_new.html.twig', array('form' => $form->createView()));
    }
}
