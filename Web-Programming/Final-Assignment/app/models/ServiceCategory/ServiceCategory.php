<?php

namespace App\Models\ServiceCategory;

Class ServiceCategory
{
	private $id;
	private $name;
	private $parent_id;
	private $create_time;
	private $update_time;

	public function __construct($id, $name, $create_time, $update_time, $parent_id)
	{
		$this->setId($id);
		$this->setName($name);
		$this->setCreateTime($create_time);
		$this->setUpdateTime($update_time);
		$this->setParentId($parent_id);
	}
    public function getId()
    {
        return $this->id;
    }
    public function getName()
    {
        return $this->name;
    }
    public function getParentId()
    {
        return $this->parent_id;
    }
    public function getCreatedTime()
    {
        return $this->created_time;
    }
    public function getUpdatedTime()
    {
        return $this->updated_time;
    }
    private function setId($id)
    {
        $this->id = $id;

        return $this;
    }
    private function setName($name)
    {
        $this->name = $name;

        return $this;
    }
    private function setParentId($parent_id)
    {
        $this->parent_id = $parent_id;

        return $this;
    }
    private function setCreateTime($created_time)
    {
        $this->created_time = $created_time;

        return $this;
    }
    private function setUpdateTime($updated_time)
    {
        $this->updated_time = $updated_time;

        return $this;
    }
}
