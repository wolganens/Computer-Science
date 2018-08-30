<?php use App\Views\Helpers\FormHelper;  ?>
<h1 class="page-header">Meus endereços</h1>

<div class="row">
	<div class="col-md-8">
		<div class="base">
			<div class="panel panel-default">
				<div class="panel-heading">
					Meus endereços
				</div>
				<div class="panel-body">
					<table class="table">
						<thead>
							<tr>
								<th>CEP</th>
								<th>Bairro</th>
								<th>Rua</th>
								<th>Número</th>
								<th>Complemento</th>
							</tr>
						</thead>
						<tbody>
							<?php foreach ($addresses as $key => $address): ?>
								<tr>
									<td><?php echo $address->getPostalCode(); ?></td>
									<td><?php echo $address->getDistrict(); ?></td>
									<td><?php echo $address->getStreet(); ?></td>
									<td><?php echo $address->getNumber(); ?></td>
									<td><?php echo $address->getComplement(); ?></td>
								</tr>
							<?php endforeach; ?>
						</tbody>
					</table>
				</div>
			</div>
		</div>
	</div>
	<div class="col-md-4">
		
	</div>
</div>