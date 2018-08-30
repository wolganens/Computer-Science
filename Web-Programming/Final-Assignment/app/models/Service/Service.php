<?php

namespace App\Models\Service;

Class Service
{
	private $id;
    private $category;
	private $address;
	private $client;
	private $price;
	private $professional;
	private $observation;
	private $paid;

	public function __construct($category, $address, $client, $professional, $paid, $observation, $price)
	{
        $this->setCategory($category);
		$this->address = $address;
		$this->client = $client;
		$this->price = $price;
		$this->professional = $professional;
		$this->observation = $observation;
		$this->paid = $paid;
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
    public function getAddress()
    {
        return $this->address;
    }
    public function setAddress($address)
    {
        $this->address = $address;

        return $this;
    }
    public function getClient()
    {
        return $this->client;
    }
    public function setClient($client)
    {
        $this->client = $client;

        return $this;
    }
    public function getPrice()
    {
        return $this->price;
    }
    public function setPrice($price)
    {
        $this->price = $price;

        return $this;
    }
    public function getProfessional()
    {
        return $this->professional;
    }
    public function setProfessional($professional)
    {
        $this->professional = $professional;

        return $this;
    }
    public function getObservation()
    {
        return $this->observation;
    }
    public function setObservation($observation)
    {
        $this->observation = $observation;
        return $this;
    }
    public function getPaid()
    {
        return $this->paid;
    }
    public function setPaid($paid)
    {
        $this->paid = $paid;

        return $this;
    }
    public function getCategory()
    {
        return $this->category;
    }
    public function setCategory($category)
    {
        $this->category = $category;

        return $this;
    }
    public function getStatus()
    {
        if ($this->getPrice()) {
            return '<span class="text-info">Orçamento feito</span>';
        } else {
            return '<span class="text-warning">Aguardando orçamento</span>';
        }
    }
}