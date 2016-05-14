<?php

namespace AppBundle\Handler;

use Symfony\Component\Security\Core\Authentication\Token\TokenInterface;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\HttpFoundation\RedirectResponse;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Security\Http\Logout\LogoutHandlerInterface;
use Doctrine\ORM\EntityManager;

class LogoutHandler implements LogoutHandlerInterface {
    private $em;

    public function __construct(EntityManager $em)
    {
        $this->em = $em;
    }

    public function logout(Request $request, Response $response, TokenInterface $token)
    {
        $user = $token->getUser();
        if(null != $pos = $this->em->getRepository('AppBundle:Position')->findOneByAssignedUser($user)) {
            $pos->setAssignedUser(); // Freeing up the position
            $this->em->flush();
        }
        $request->getSession()->invalidate();
    }
}
