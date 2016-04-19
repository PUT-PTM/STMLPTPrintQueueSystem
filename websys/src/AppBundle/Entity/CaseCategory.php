<?php

namespace AppBundle\Entity;

use Doctrine\Common\Collections\ArrayCollection;
use Doctrine\ORM\Mapping as ORM;

/**
 * CaseCategory
 *
 * @ORM\Table(name="case_category")
 * @ORM\Entity(repositoryClass="AppBundle\Repository\CaseCategoryRepository")
 */
class CaseCategory
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
     * @ORM\Column(name="name", type="string", length=64)
     */
    private $name;

    /**
     * @var string
     *
     * @ORM\Column(name="shortcut", type="string", length=3, unique=true)
     */
    private $shortcut;

    /**
     * @var ArrayCollection
     *
     * @ORM\OneToMany(targetEntity="PetitionerNumber", mappedBy="caseCategory")
     */
    private $petitionerNumbers;


    public function __construct()
    {
        $this->petitionerNumbers = new ArrayCollection();
    }

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
     * @return CaseCategory
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
     * Set shortcut
     *
     * @param string $shortcut
     *
     * @return CaseCategory
     */
    public function setShortcut($shortcut)
    {
        $this->shortcut = $shortcut;

        return $this;
    }

    /**
     * Get shortcut
     *
     * @return string
     */
    public function getShortcut()
    {
        return $this->shortcut;
    }

    /**
     * Add petitionerNumber
     *
     * @param \AppBundle\Entity\PetitionerNumber $petitionerNumber
     *
     * @return CaseCategory
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
