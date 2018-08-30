<?php

namespace App\Models\Professional;

use App\Models\Db;
use Exception;
use PDO;
use PDOException;

Class ProfessionalDao
{
	private $db;

	public function __construct()
	{
		$this->db = Db::getInstance()->getConnection();
		$this->db->setAttribute (PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	}

	public function insert($professional)
	{
		try {
			$sql = 'INSERT INTO user (name, email, password, phone_number, identity_number) 
				values (:name, :email, :password, :phone_number, :identity_number)';
			$sth = $this->db->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':name', $professional->getName());
			$sth->bindValue(':email', $professional->getEmail());
			$sth->bindValue(':password', $professional->getPassword());
			$sth->bindValue(':phone_number', $professional->getPhoneNumber());
			$sth->bindValue(':identity_number', $professional->getIdentityNumber() ?? '');
			$results = $sth->execute();
		} catch (PDOException $e) {
			throw new Exception($e->getMessage(), $e->getCode());
		}
		$user_id = $this->db->lastInsertId();
		try {
			$sql = 'INSERT INTO professional (id) values (:id);';
			$sth = $this->db->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
			$sth->bindValue(':id', $user_id);
			$results = $sth->execute();
		} catch (PDOException $e) {
			throw new Exception($e->getMessage(), $e->getCode());
		}
		return (!$results ? $this->db->errorInfo() : $user_id);
	}
	public function retrieve()
	{
		$query = 'SELECT * FROM professional';
		return $this->db->query($query);
	}
	public function update($professional)
	{
	}
	public function delete($professional)
	{
		echo "teste";
	}
	public function getDb()
    {
        return $this->db;
    }
}