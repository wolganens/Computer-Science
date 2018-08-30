<?php

namespace App\Models\Http;

Class Input
{
	public static function get($name, $default = null)
	{
		return $_POST[$name] ?? $_GET[$name] ?? $default;
	}
}