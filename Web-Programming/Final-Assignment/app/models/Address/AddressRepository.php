<?php

namespace App\Models\Address;
use PDOException;
use PDO;
use Exception;

Class AddressRepository
{
	public $collection = [];
	private $dao;

	public function __construct()
	{
		$this->dao = new AddressDao();
	}
	public function all()
	{
		return $this->mapToModel($this->dao->retrieve());
	}
	public function create($postal_code, $complement, $district, $number, $street)
	{
		$address = new Address($postal_code, $complement, $district, $number, $street);
		try {
			$address->setId($this->dao->insert($address));
		} catch (Exception $e) {
			return $e->getMessage();
		}
		return $address;
	}
	public function findByUser($user_id)
	{
		try {
			$sql = 'SELECT * FROM service
			INNER JOIN user on service.client_id = user.id and user.id = :user_id
			INNER JOIN address on service.address_id = address.id';

			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':user_id', $user_id);
			$results = $sth->execute();
			$address = $this->mapToModel($sth);
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}
		return $address ? $address : null;
	}
	public function findById($id)
	{
		try {
			$sql = 'SELECT * FROM address where id = :id';
			$sth = $this->dao->getDb()->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':id', $id);
			$results = $sth->execute();
			$address = $this->mapToModel($sth);
		} catch (PDOException $e) {
			var_dump($e);
			exit;
		}
		return $address ? $address : null;
	}
	private function mapToModel($results)
	{
		if ($results->rowCount() == 0) {
			return false;
		}
		foreach ($results as $model) {
			$id = $model['id'];
			$city = 1;
			$postal_code = $model['postal_code'];
			$complement = $model['complement'];
			$district = $model['district'];
			$number = $model['number'];
			$street = $model['street'];
			$address = new Address($postal_code, $complement, $district, $number, $street);
			$address->setId($id);
			$this->collection[] = $address;
		}
		if ($results->rowCount() == 1) {
			return $address;
		} else {
			return $this->collection;
		}
	}
}