<?php

namespace AppBundle\Entity;

use Doctrine\ORM\Mapping as ORM;

/**
 * PetitionerNumber
 *
 * @ORM\Table(name="petitioner_number")
 * @ORM\Entity(repositoryClass="AppBundle\Repository\PetitionerNumberRepository")
 */
class PetitionerNumber
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
     * @ORM\Column(name="generatedNum", type="string", length=10)
     */
    private $generatedNum;

    /**
     * @var \DateTime
     *
     * @ORM\Column(name="createdOn", type="datetime")
     */
    private $createdOn;

    /**
     * @var \DateTime
     *
     * @ORM\Column(name="updatedOn", type="datetime", nullable=true)
     */
    private $updatedOn;

    /**
     * @var Status
     *
     * @ORM\ManyToOne(targetEntity="Status", inversedBy="petitionerNumbers")
     * @ORM\JoinColumn(name="status_id", referencedColumnName="id")
     */
    private $status;

    /**
     * @var User
     *
     * @ORM\ManyToOne(targetEntity="User", inversedBy="petitionerNumbers")
     * @ORM\JoinColumn(name="assigned_user_id", referencedColumnName="id")
     */
    private $assignedUser;

    /**
     * @ORM\ManyToOne(targetEntity="Position", inversedBy="petitionerNumbers")
     * @ORM\JoinColumn(name="position_id", referencedColumnName="id")
     */
    private $position;

    /**
     * @var CaseCategory
     *
     * @ORM\ManyToOne(targetEntity="CaseCategory", inversedBy="petitionerNumbers")
     * @ORM\JoinColumn(name="case_category_id", referencedColumnName="id")
     */
    private $caseCategory;


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
     * Set generatedNum
     *
     * @param string $generatedNum
     *
     * @return PetitionerNumber
     */
    public function setGeneratedNum($generatedNum)
    {
        $this->generatedNum = $generatedNum;

        return $this;
    }

    /**
     * Get generatedNum
     *
     * @return string
     */
    public function getGeneratedNum()
    {
        return $this->generatedNum;
    }

    /**
     * Set createdOn
     *
     * @param \DateTime $createdOn
     *
     * @return PetitionerNumber
     */
    public function setCreatedOn($createdOn)
    {
        $this->createdOn = $createdOn;

        return $this;
    }

    /**
     * Get createdOn
     *
     * @return \DateTime
     */
    public function getCreatedOn()
    {
        return $this->createdOn;
    }

    /**
     * Set updatedOn
     *
     * @param \DateTime $updatedOn
     *
     * @return PetitionerNumber
     */
    public function setUpdatedOn($updatedOn)
    {
        $this->updatedOn = $updatedOn;

        return $this;
    }

    /**
     * Get updatedOn
     *
     * @return \DateTime
     */
    public function getUpdatedOn()
    {
        return $this->updatedOn;
    }

    /**
     * Set position
     *
     * @param \AppBundle\Entity\Position $position
     *
     * @return PetitionerNumber
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

    /**
     * Set status
     *
     * @param \AppBundle\Entity\Status $status
     *
     * @return PetitionerNumber
     */
    public function setStatus(\AppBundle\Entity\Status $status = null)
    {
        $this->status = $status;

        return $this;
    }

    /**
     * Get status
     *
     * @return \AppBundle\Entity\Status
     */
    public function getStatus()
    {
        return $this->status;
    }

    /**
     * Set assignedUser
     *
     * @param \AppBundle\Entity\User $assignedUser
     *
     * @return PetitionerNumber
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
     * Set caseCategory
     *
     * @param \AppBundle\Entity\CaseCategory $caseCategory
     *
     * @return PetitionerNumber
     */
    public function setCaseCategory(\AppBundle\Entity\CaseCategory $caseCategory = null)
    {
        $this->caseCategory = $caseCategory;

        return $this;
    }

    /**
     * Get caseCategory
     *
     * @return \AppBundle\Entity\CaseCategory
     */
    public function getCaseCategory()
    {
        return $this->caseCategory;
    }
}
