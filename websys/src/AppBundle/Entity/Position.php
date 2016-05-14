<?php
namespace AppBundle\Entity;

use Doctrine\ORM\Mapping as ORM;

/**
 * @ORM\Entity
 * @ORM\Table(name="position")
 */
class Position 
{
    /**
     * @var int
     *
     * @ORM\Column(name="id", type="integer")
     * @ORM\Id
     * @ORM\GeneratedValue(strategy="AUTO")
     */
    private $id;
    
    /**
     * @var string
     * 
     * @ORM\Column(name="name", type="string", length=32, unique=true)
     */
    private $name;
    
    /**
     * @ORM\OneToOne(targetEntity="User", mappedBy="position")
     * @ORM\JoinColumn(name="assigned_user_id", referencedColumnName="id")
     */
    private $assignedUser;
    
    /**
     * @ORM\OneToMany(targetEntity="PetitionerNumber", mappedBy="position")
     */
    private $petitionerNumbers;

    /**
     * Get id
     *
     * @return integer
     */
    public function getId()
    {
        return $this->id;
    }

    /**
     * Set name
     *
     * @param string $name
     *
     * @return Station
     */
    public function setName($name)
    {
        $this->name = $name;

        return $this;
    }

    /**
     * Get name
     *
     * @return string
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * Set assignedUser
     *
     * @param \AppBundle\Entity\User $assignedUser
     *
     * @return Station
     */
    public function setAssignedUser(\AppBundle\Entity\User $assignedUser = null)
    {
        $this->assignedUser = $assignedUser;

        return $this;
    }

    /**
     * Get assignedUser
     *
     * @return \AppBundle\Entity\User
     */
    public function getAssignedUser()
    {
        return $this->assignedUser;
    }
    /**
     * Constructor
     */
    public function __construct()
    {
        $this->petitionerNumbers = new \Doctrine\Common\Collections\ArrayCollection();
    }

    /**
     * Add petitionerNumber
     *
     * @param \AppBundle\Entity\PetitionerNumber $petitionerNumber
     *
     * @return Position
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
}
