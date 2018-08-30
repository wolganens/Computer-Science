<?php

namespace App\Models\Address;

use App\Models\Db;
use Exception;
use PDO;
use PDOException;

Class AddressDao
{
	private $db;

	public function __construct()
	{
		$this->db = Db::getInstance()->getConnection();
	}
	public function insert($address)
	{
		try {
			$sql = 'INSERT INTO address (city_id, postal_code, complement, district, number, street) values (1, :postal_code, :complement, :district, :number, :street)';
			$sth = $this->db->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':postal_code', $address->getPostalCode());
			$sth->bindValue(':complement', $address->getComplement());
			$sth->bindValue(':district', $address->getDistrict());
			$sth->bindValue(':number', $address->getNumber());
			$sth->bindValue(':street', $address->getStreet());
			$results = $sth->execute();
		} catch (PDOException $e) {
			throw new Exception($e->getMessage(), $e->getCode());
		}
		return (!$results ? $this->db->errorInfo() : $this->db->lastInsertId());
	}
	public function retrieve()
	{
		$query = 'SELECT * FROM address';
		return $this->db->query($query);
	}
	public function update($address)
	{
		echo "teste";
	}
	public function delete($address)
	{
		echo "teste";
	}
	public function getDb()
    {
        return $this->db;
    }
}