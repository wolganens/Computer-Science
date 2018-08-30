<?php use App\Views\Helpers\FormHelper;  ?>
<h1 class="page-header">Meus Serviços</h1>

<div class="base">
	<div class="row">
		<div class="col-md-8">
			<div class="panel panel-default">
				<div class="panel-heading">
					Serviços
				</div>
				<div class="panel-body">
					<table class="table">
						<thead>
							<tr>
								<th>Categoria</th>
								<th>Profissional</th>
								<th>Endereço</th>
								<th>Status</th>
								<th>Preço</th>
							</tr>
						</thead>
						<tbody>
							<?php foreach ($services as $key => $service): ?>
								<tr>
									<td><?php echo $service->getCategory()->getName(); ?></td>
									<td><?php echo $service->getProfessional()->getName(); ?></td>
									<td><?php echo $service->getAddress()->getAddressString(); ?></td>
									<td><?php echo $service->getStatus(); ?></td>
									<td><?php echo $service->getPrice(); ?></td>
								</tr>
							<?php endforeach; ?>
						</tbody>
					</table>
				</div>
			</div>
		</div>
		<div class="col-md-4">
			<div class="panel panel-primary">
				<div class="panel-heading">
					Novo serviço
				</div>
				<div class="panel-body">
					<form action="index.php?controller=Service&action=postCreate" method="POST">
						<?php echo FormHelper::select('Qual o tipo de serviço?', 'category', $categories, null, null) ?>
						<?php echo FormHelper::select('Selecione um endereço', 'address', ['' => 'Selecione um endereço'] + ($addresses ?? []), null, null) ?>
						<p class="text-center">Ou cadastre um novo endereço</p>
						<?php echo FormHelper::text('CEP', 'postal-code', null, null); ?>
						<?php echo FormHelper::text('Bairro', 'district', null, null); ?>
						<?php echo FormHelper::text('Rua', 'street', null, null); ?>
						<?php echo FormHelper::text('Número', 'number', null, null); ?>
						<?php echo FormHelper::text('Complemento', 'complement', null, null); ?>
						<?php echo FormHelper::submit('Solicitar', 'btn-block') ?>
					</form>
				</div>
			</div>
		</div>
	</div>
</div>