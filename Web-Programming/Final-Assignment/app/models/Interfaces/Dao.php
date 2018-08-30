<?php

namespace App\Models\Interfaces;

Interface Dao
{
	public function insert($model);	
	public function retrieve();
	public function update($model);
	public function delete($model);
}