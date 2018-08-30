<?php

namespace App\Models\Professional;

use App\Models\Professional\Professional;
use App\Models\Professional\ProfessionalDao;
use App\Models\ServiceCategory\ServiceCategoryRepository;
use Exception;
use PDO;
use PDOException;

Class ProfessionalRepository
{
	private $collection = [];
	private $dao;

	public function __construct()
	{
		$this->dao = new ProfessionalDao();
	}

	public function create($name, $email, $password, $phone_number = null, $identity_number = null)
	{
		$professional = new Professional($name, $email, $password, $phone_number, $identity_number, []);
		try {
			$professional->setId($this->dao->insert($professional));
		} catch (Exception $e) {
			return $e->getMessage();
		}		
		return $professional;
	}
	public function findById($id)
	{
		$professional;
		try {
			$sql = 'SELECT * FROM professional INNER JOIN user on user.id = professional.id and  user.id = :id LIMIT 1';
			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':id', $id);
			$results = $sth->execute();
			$professional = $this->mapToModel($sth);
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}
		return $professional ? $professional : null;
	}
	/**
	 * Busca um profissional pelo $email;
	 */
	public function findByEmail($email)
	{
		try {
			$sql = 'SELECT * FROM professional INNER JOIN user on user.id = professional.id and email = :email LIMIT 1;';
			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':email', $email);
			$results = $sth->execute();
			$professional = $this->mapToModel($sth);
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}
		return $professional ? $professional : null;
	}
	public function updateCategories($professional, $categories)
	{
		/**
		 * Remove todas as categorias do profissional antes de atualizá-las
		 */
		try {
			$sql = 'DELETE FROM professional_has_service_category where professional_id = :professional_id;';
			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':professional_id', $professional->getId());
			$results = $sth->execute();
		} catch (PDOException $e) {
			var_dump($e);
			exit;	
		}
		/**
		 * Insere as categorias do profissional na tabela resultante do N:N de profissionalXcategoria
		 */
		if (!empty($categories)) {
			foreach ($categories as $key => $service_category_id) {
				try {
					$sql = 'INSERT INTO professional_has_service_category (professional_id, service_category_id) VALUES (:professional_id, :service_category_id);';
					$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
					$sth->bindValue(':professional_id', $professional->getId());
					$sth->bindValue(':service_category_id', $service_category_id);
					$results = $sth->execute();
				} catch (PDOException $e) {
					var_dump($e);
					exit;	
				}
			}
		}
		$professional->setCategories($categories);
		return $professional;
	}
	/**
	 * Retorna os profissionais que trabalham em uma categoria
	 */
	public function findByCategory($service_category_id)
	{
		try {
			$sql = 'SELECT * FROM professional
			INNER JOIN user on professional.id = user.id
			INNER JOIN professional_has_service_category on professional.id = professional_has_service_category.professional_id 
			and professional_has_service_category.service_category_id = :service_category_id;';

			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':service_category_id', $service_category_id);
			$results = $sth->execute();
			$professional = $this->mapToModel($sth);
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}
		return $professional ? $professional : null;
	}
	/**
	 * Percorre os resultados de uma consulta e mapeia para a model;
	 */
	private function mapToModel($results)
	{
		$professional;
		/**
		 * Não encontrou nenhum resultado
		 */
		if ($results->rowCount() == 0) {
			return false;
		}
		/**
		 * Para mais de um resultado, instancia os objetos
		 */
		foreach ($results as $model) {
			$id = $model['id'];
			$name = $model['name'];
		    $email = $model['email'];
		    $password = $model['password'];
		    $phone_number = $model['phone_number'];
		    $identity_number = $model['identity_number'];
			
			$professional = new Professional($name, $email, $password, $phone_number, $identity_number, 2);
			$professional->setId($id);
			$this->appendProfessionalCategories($professional);
			$this->collection[] = $professional;
		}
		/**
		 * Para um resultado, retorna o único objeto, se não for único retorna toda a coleção
		 */
		if ($results->rowCount() == 1) {
			$this->appendProfessionalCategories($professional);
			return $professional;
		} else {
			return $this->collection;
		}
	}
	/**
	 * Mapeia para a model de um profissional, todas suas categorias
	 */
	private function appendProfessionalCategories($professional)
	{
		$category_repository = new ServiceCategoryRepository();
		$categories = $category_repository->findByProfessional($professional->getId());
		$cat_ids = [];
		foreach ($categories as $category) {
			$cat_ids[] = $category->getId();
		}
		$professional->setCategories($cat_ids);
		return $professional;
	}
}