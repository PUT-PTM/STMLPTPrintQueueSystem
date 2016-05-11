<?php

namespace AppBundle\Entity;

use Doctrine\Common\Collections\ArrayCollection;
use Doctrine\ORM\Mapping as ORM;

/**
 * Status
 *
 * @ORM\Table(name="status")
 * @ORM\Entity(repositoryClass="AppBundle\Repository\StatusRepository")
 */
class Status
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
     * @var ArrayCollection
     *
     * @ORM\OneToMany(targetEntity="PetitionerNumber", mappedBy="status")
     */
    private $petitionerNumbers;

    /**
     * Get id
     *
     * @return int
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
     * @return Status
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
     * @return Status
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
