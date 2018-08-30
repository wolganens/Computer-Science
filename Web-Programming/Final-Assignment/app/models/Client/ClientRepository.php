<?php

namespace App\Models\Client;

use App\Models\Client\ClientDao;
use PDOException;
use PDO;
use Exception;

Class ClientRepository
{	
	protected $collection = [];
	
	private $dao;

	public function __construct()
	{
		$this->dao = new ClientDao();
	}
	public function all()
	{
		return $this->mapToModel($this->dao->retrieve());
	}
	public function create($name, $email, $password, $phone_number = null, $identity_number = null)
	{		
		$client = new Client($name, $email, $password, $phone_number, $identity_number);
		try {
			$client->setId($this->dao->insert($client));
		} catch (Exception $e) {
			return $e->getMessage();
		}		
		return $client;
	}
	public function findById($id)
	{
		$client;
		try {
			$sql = 'SELECT * FROM client INNER JOIN user on user.id = client.id and  user.id = :id LIMIT 1';
			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':id', $id);
			$results = $sth->execute();
			$client = $this->mapToModel($sth);
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}
		return $client ? $client : null;
	}
	public function findByEmail($email)
	{
		try {
			$sql = 'SELECT * FROM client INNER JOIN user on user.id = client.id and email = :email LIMIT 1;';
			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':email', $email);
			$results = $sth->execute();
			$client = $this->mapToModel($sth);
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}	
		return $client ? $client : null;
	}
	public function findByProfessional($professional_id)
	{
		try {
			$sql = 'SELECT * FROM service
				INNER JOIN professional on professional.id = service.professional_id and service.professional_id = :professional_id
				INNER JOIN client on client.id = service.client_id
				INNER JOIN user on service.client_id = user.id group by service.client_id';
			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':professional_id', $professional_id);
			$results = $sth->execute();
			$client = $this->mapToModel($sth);
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}	
		return $client ? $client : null;
	}
	/**
	 * Percorre os resultados de uma consulta e mapeia para a model;
	 */
	private function mapToModel($results)
	{
		$client;
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
			
			$client = new Client($name, $email, $password, $phone_number, $identity_number, 1);
			$client->setId($id);
			$this->collection[] = $client;
		}
		/**
		 * Para um resultado, retorna o único objeto, se não for único retorna toda a coleção
		 */
		if ($results->rowCount() == 1) {
			return $client;
		} else {
			return $this->collection;
		}
	}
}