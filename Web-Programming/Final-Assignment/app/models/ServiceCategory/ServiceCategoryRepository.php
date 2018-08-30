<?php

namespace App\Models\ServiceCategory;

use Exception;
use PDO;
use PDOException;

Class ServiceCategoryRepository
{	
	protected $collection = [];
	
	private $dao;

	public function __construct()
	{
		$this->dao = new ServiceCategoryDao();
	}
	public function all()
	{
		return $this->mapToModel($this->dao->retrieve());
	}
	public function findByProfessional($professional)
	{
		try {
			$sql = 'SELECT * FROM service_category 
				INNER JOIN professional_has_service_category on 
				service_category.id = professional_has_service_category.service_category_id 
				and professional_has_service_category.professional_id = :professional_id';
				
			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':professional_id', $professional);
			$results = $sth->execute();
			$category = $this->mapToModel($sth);
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}
		return $category ? $category : null;
	}
	public function findById($id)
	{
		try {
			$sql = 'SELECT * FROM service_category where id = :id';				
			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':id', $id);
			$results = $sth->execute();
			$category = $this->mapToModel($sth);
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}
		return $category ? $category : null;
	}
	/**
	 * Percorre os resultados de uma consulta e mapeia para a model;
	 */
	private function mapToModel($results)
	{
		$category;
		if ($results->rowCount() == 0) {
			return false;
		}
		foreach ($results as $model) {			
			$id = $model['id'];
			$name = $model['name'];
			$create_time = $model['created_at'];
			$update_time = $model['updated_at'];
			$patent_id = $model['parent_id'];
			$category = new ServiceCategory($id, $name, $create_time, $update_time, $patent_id);
			$this->collection[] = $category;

		}		
		if ($results->rowCount() == 1) {
			return $category;
		} else {
			return $this->collection;
		}
	}
}