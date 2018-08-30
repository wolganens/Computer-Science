<?php

namespace App\Models\User;

use App\Models\Db;
use Exception;
use PDO;

Class UserDao
{
	private $db;

	public function __construct()
	{
		$this->db = Db::getInstance()->getConnection();
	}
	public function insert($user)
	{
		$query = sprintf('INSERT INTO user (name, email, password, phone_number, identity_number) values ("%s", "%s", "%s", "%s", "%s")', $user->getName(), $user->getEmail(), $user->getPassword(), $user->getPhoneNumber(), $user->getIdentityNumber());
		return $this->db->query($query);
	}	
	public function retrieve()
	{
		$query = 'SELECT * FROM user';
		return $this->db->query($query);
	}
	public function update($user)
	{
		echo "teste";
	}
	public function delete($user)
	{
		echo "teste";
	}    
    public function getDb()
    {
        return $this->db;
    }
}