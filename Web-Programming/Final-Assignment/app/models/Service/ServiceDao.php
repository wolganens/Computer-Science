<?php

namespace App\Models\Service;

use App\Models\Db;
use Exception;
use PDO;
use PDOException;
use App\Models\Service\Service;

Class ServiceDao
{
	private $db;

	public function __construct()
	{
		$this->db = Db::getInstance()->getConnection();
	}
	public function insert($service)
	{
		try {
			$sql = 'INSERT INTO service (service_category_id, address_id, client_id, price, professional_id, observation, paid) values (:service_category_id, :address_id, :client_id, :price, :professional_id, :observation, :paid)';
			$sth = $this->db->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':service_category_id', $service->getCategory());
			$sth->bindValue(':address_id', $service->getAddress());
			$sth->bindValue(':client_id', $service->getClient());
			$sth->bindValue(':price', $service->getPrice());
			$sth->bindValue(':professional_id', $service->getProfessional());
			$sth->bindValue(':observation', $service->getObservation());
			$sth->bindValue(':paid', $service->getPaid());
			$results = $sth->execute();
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}
		return (!$results ? $this->db->errorInfo() : $this->db->lastInsertId());
	}
	public function retrieve()
	{
		$query = 'SELECT * FROM service';
		return $this->db->query($query);
	}
	public function update($client)
	{
		echo "teste";
	}
	public function delete($client)
	{
		echo "teste";
	}
	public function getDb()
    {
        return $this->db;
    }
}