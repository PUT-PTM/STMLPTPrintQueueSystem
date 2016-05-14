<?php
namespace AppBundle\Entity;

use Doctrine\Common\Collections\ArrayCollection;
use FOS\UserBundle\Model\User as BaseUser;
use Doctrine\ORM\Mapping as ORM;

/**
* @ORM\Entity
* @ORM\Table(name="user")
*/
class User extends BaseUser
{
    /**
    * @ORM\Id
    * @ORM\Column(type="integer")
    * @ORM\GeneratedValue(strategy="AUTO")
    */
    protected $id;

    /**
     * @var ArrayCollection
     *
     * @ORM\OneToMany(targetEntity="PetitionerNumber", mappedBy="assignedUser")
     */
    private $petitionerNumbers;

    /**
     * @ORM\OneToOne(targetEntity="Position", mappedBy="assignedUser")
     */
    private $position;

    /**
     * User constructor.
     */
    public function __construct()
    {
    parent::__construct();
    // your own logic
    }

    /**
     * Add petitionerNumber
     *
     * @param \AppBundle\Entity\PetitionerNumber $petitionerNumber
     *
     * @return User
     */
    public function addPetitionerNumber(\AppBundle\Entity\PetitionerNumber $petitionerNumber)
    {
        $this->petitionerNumbers[] = $petitionerNumber;

        return $this;
    }

    /**
     * Remove petitionerNumber
     *
     * @param \AppBundle\Entity\PetitionerNumber $petitionerNumber
     */
    public function removePetitionerNumber(\AppBundle\Entity\PetitionerNumber $petitionerNumber)
    {
        $this->petitionerNumbers->removeElement($petitionerNumber);
    }

    /**
     * Get petitionerNumbers
     *
     * @return \Doctrine\Common\Collections\Collection
     */
    public function getPetitionerNumbers()
    {
        return $this->petitionerNumbers;
    }

    /**
     * Set position
     *
     * @param \AppBundle\Entity\Position $position
     *
     * @return User
     */
    public function setPosition(\AppBundle\Entity\Position $position = null)
    {
        $this->position = $position;

        return $this;
    }

    /**
     * Get position
     *
     * @return \AppBundle\Entity\Position
     */
    public function getPosition()
    {
        return $this->position;
    }
}
