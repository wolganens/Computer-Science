<?php

namespace App\Models\Http;

Class Redirect
{
	public static function url($url, $params = [])
	{
		unset($_SESSION['params']);
		foreach ($params as $key => $param) {
			$params[$key] = serialize($param);
		}
		$_SESSION['params'] = $params;
		header(sprintf('Location: %s', $url));
		die();
	}
}