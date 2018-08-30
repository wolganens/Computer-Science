<?php

namespace App\Models\Service;

use PDOException;
use PDO;
use Exception;
use App\Models\Professional\ProfessionalRepository;
use App\Models\Client\ClientRepository;
use App\Models\ServiceCategory\ServiceCategoryRepository;
use App\Models\Address\AddressRepository;

Class ServiceRepository
{
	public $collection = [];
	private $dao;
	private $service_category_repository;
	private $professional_repository;
	private $address_repositorty;
	private $client_repository;

	public function __construct()
	{
		$this->dao = new ServiceDao();
		$this->service_category_repository = new ServiceCategoryRepository();
		$this->professional_repository = new ProfessionalRepository();
		$this->address_repositorty = new AddressRepository();
		$this->client_repository = new ClientRepository();
	}
	public function all()
	{
		return $this->mapToModel($this->dao->retrieve());
	}
	public function create($category, $address, $client, $service, $paid = null, $observation = null, $price = null)
	{
		$service = new Service($category, $address, $client, $service, $paid, $observation, $price);
		try {
			$service->setId($this->dao->insert($service));
		} catch (Exception $e) {
			return $e->getMessage();
		}
		return $service;
	}
	public function findByClient($client)
	{
		$service;
		try {
			$sql = 'SELECT * FROM service where client_id = :id';
			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':id', $client);
			$results = $sth->execute();
			$service = $this->mapToModel($sth);
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}
		return $service ? $service : null;
	}
	public function findByProfessional($professional)
	{
		$service;
		try {
			$sql = 'SELECT * FROM service where professional_id = :id';
			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':id', $professional);
			$results = $sth->execute();
			$service = $this->mapToModel($sth);
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}
		return $service ? $service : null;
	}
	public function updatePrice($service_id, $price)
	{
		$service;
		try {
			$sql = 'UPDATE service 
					SET price = :price where id = :service_id';
			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':price', $price);
			$sth->bindValue(':service_id', $service_id);
			$results = $sth->execute();
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}
		return $results;
	}
	/**
	 * Percorre os resultados de uma consulta e mapeia para a model;
	 */
	private function mapToModel($results)
	{
		$service;
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
			$category = $this->service_category_repository->findById($model['service_category_id']);
		    $address = $this->address_repositorty->findById($model['address_id']);
		    $client = $this->client_repository->findById($model['client_id']);
		    $professional = $this->professional_repository->findById($model['professional_id']);
		    $paid = $model['paid'];
		    $observation = $model['observation'];
		    $price = $model['price'];
			
			$service = new service($category, $address, $client, $professional, $paid, $observation, $price);
			$service->setId($id);
			$this->collection[] = $service;
		}
		/**
		 * Para um resultado, retorna o único objeto, se não for único retorna toda a coleção
		 */
		$_SESSION['repositories']['service'] = serialize($this->collection);
		if ($results->rowCount() == 1) {
			return $service;
		} else {
			return $this->collection;
		}
	}
}