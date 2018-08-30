<?php

namespace App\Models\User;

Class Auth {
	public static function user()
	{
		return unserialize($_SESSION['user'] ?? null);
	}
	public static function updateAuthUser($user)
	{
		$_SESSION['user'] = serialize($user);
	}
}