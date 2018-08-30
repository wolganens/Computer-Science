<?php

namespace App\Models\Address;

Class Address
{
	private $id;
	private $city;
	private $postal_code;
	private $complement;
	private $district;
	private $number;
	private $street;

	function __construct($postal_code, $complement, $district, $number, $street)
	{
		$this->postal_code = $postal_code;
		$this->complement = $complement;
		$this->district = $district;
		$this->number = $number;
		$this->street = $street;
	}
    public function getId()
    {
        return $this->id;
    }
    public function setId($id)
    {
        $this->id = $id;

        return $this;
    }
    public function getCity()
    {
        return $this->city;
    }
    public function setCity($city)
    {
        $this->city = $city;

        return $this;
    }
    public function getPostalCode()
    {
        return $this->postal_code;
    }
    public function setPostalCode($postal_code)
    {
        $this->postal_code = $postal_code;

        return $this;
    }
    public function getComplement()
    {
        return $this->complement;
    }
    public function setComplement($complement)
    {
        $this->complement = $complement;

        return $this;
    }
    public function getDistrict()
    {
        return $this->district;
    }
    public function setDistrict($district)
    {
        $this->district = $district;

        return $this;
    }
    public function getNumber()
    {
        return $this->number;
    }
    public function setNumber($number)
    {
        $this->number = $number;

        return $this;
    }
    public function getStreet()
    {
        return $this->street;
    }
    public function setStreet($street)
    {
        $this->street = $street;

        return $this;
    }
    public function getAddressString()
    {
        return $this->getStreet() . ' ' . $this->getDistrict() . ' ' . $this->getNumber() . ' ' . $this->getComplement();
    }
}