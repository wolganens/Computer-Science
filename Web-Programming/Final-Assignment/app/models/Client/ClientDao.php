<?php

namespace App\Models\Client;

use App\Models\Interfaces\Dao;
use App\Models\Db;
use PDOException;
use PDO;
use Exception;

Class ClientDao implements Dao
{
	private $db;

	public function __construct()
	{
		$this->db = Db::getInstance()->getConnection();
	}
	public function insert($client)
	{
		try {
			$sql = 'INSERT INTO user (name, email, password, phone_number, identity_number) 
				values (:name, :email, :password, :phone_number, :identity_number)';
			$sth = $this->db->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':name', $client->getName());
			$sth->bindValue(':email', $client->getEmail());
			$sth->bindValue(':password', $client->getPassword());
			$sth->bindValue(':phone_number', $client->getPhoneNumber());
			$sth->bindValue(':identity_number', $client->getIdentityNumber() ?? '');
			$results = $sth->execute();
		} catch (PDOException $e) {
			throw new Exception($e->getMessage(), $e->getCode());
		}
		try {
			$sql = 'INSERT INTO client (id) values (:id);';
			$sth = $this->db->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':id', $this->db->lastInsertId());
			$results = $sth->execute();
		} catch (PDOException $e) {
			throw new Exception($e->getMessage(), $e->getCode());
		}
		return (!$results ? $this->db->errorInfo() : $this->db->lastInsertId());
	}
	public function retrieve()
	{
		$query = 'SELECT * FROM client';
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