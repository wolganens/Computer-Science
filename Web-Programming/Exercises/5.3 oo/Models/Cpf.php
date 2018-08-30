<?php

Class Cpf {
	public static function validate($cpf) {
		$cpf  = preg_replace('/[.-]/', '', $cpf);
		$i = 0;
		$j = 10;
		$aux = 0;
		if (strlen($cpf) != 11) {
			throw new Exception("Cpf deve ter 11 caracteres", 1);
		}
		for ($i = 0 ; $i < 9 ; $i++) {
			$aux += $cpf[$i] * $j;
			--$j;
		}
		$aux = $aux % 11;
		$aux = 11 - $aux;

		if ($aux > 9) {
			$aux = 0;
		}
		$dv_1 = $aux;

		$j = 11;
		$aux = 0;
		for ($i = 0 ; $i < 9 ; $i++) {
			$aux += $cpf[$i] * $j;
			--$j;
		}
		$aux += $dv_1 * $j;
		$aux = $aux % 11;

		$aux = 11 - $aux;

		if ($aux > 9) {
			$aux = 0;
		}
		if (! ($dv_1 == $cpf[9] && $aux == $cpf[10]) ) {
			throw new Exception("Número de CPF inválido", 1);
		} else {
			return $cpf;
		}
	}
}