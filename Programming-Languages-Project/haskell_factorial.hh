<?hh
	function recursive_fatorial(int $n): int{
		return $n == 0 ? 1 : $n * fatorial($n - 1);
	}
	function iterative_fatorial(int $n): int{
		if ($n < 2) {
			return 1;
		}
		return iterative_fatorial($n - 1);
	}
	function matrix_multiplication(){
		array<array> $arr = array(array());
		array<array> $res = array(array());
		int $tam = 3;
		
		for ($i=0; $i < $tam; $i++) { 
			for ($j=0; $j < $tam; $j++) { 
				$arr[$i][$j] = $i+$j;
				$res[$i][$j] = 0;
			}
		}
		
		for ($i=0; $i < $tam; $i++) { 
			for ($j=0; $j < $tam; $j++) { 
				for ($k=0; $k < ; $k++) { 
					$res[$i][$j] += $arr[$k][$j]*$arr[$i][$k];
				}
			}
		}


		print_r($res);

	}





?>