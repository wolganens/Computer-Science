<?php

namespace App\Models\ServiceCategory;

use App\Models\Db;

Class ServiceCategoryDao
{
	private $db;

	public function __construct()
	{
		$this->db = Db::getInstance()->getConnection();
	}
	public function insert($service_category)
	{
		echo "teste";
	}	
	public function retrieve()
	{
		$query = 'SELECT * FROM service_category';
		return $this->db->query($query);
	}
	public function update($service_category)
	{
		echo "teste";
	}
	public function delete($service_category)
	{
		echo "teste";
	}
	public function getDb()
	{
		return $this->db;
	}
}