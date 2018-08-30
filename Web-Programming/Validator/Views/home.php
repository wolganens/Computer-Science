<?php if (isset($success)): ?>
	<div class="alert alert-success">
		<?php echo $success; ?>
	</div>
<?php endif; ?>
<?php if (isset($danger)): ?>
	<div class="alert alert-danger">
		<?php echo $danger; ?>
	</div>
<?php endif; ?>
<form action="index.php?controller=Pages&action=register" method="POST" role="form">
	<legend>Cadastro</legend>
	<div class="row">
		<div class="col-sm-6">
			<?php echo FormHelper::text('Nome', 'name', $_POST['name'], ['placeholder' => 'Digite seu nome']); ?>
		</div>
		<div class="col-sm-6">
			<?php echo FormHelper::text('Data (xx/xx/xxxx)', 'date', $_POST['date'], ['placeholder' => 'Ex: 05/02/2018']); ?>
		</div>
	</div>
	<div class="row">
		<div class="col-sm-6">
			<?php echo FormHelper::text('CPF', 'cpf', $_POST['cpf'], ['placeholder' => 'Digite seu CPF']); ?>
		</div>
		<div class="col-sm-6">
			<?php echo FormHelper::text('Email', 'email', $_POST['email'], ['placeholder' => 'Digite seu email']); ?>
		</div>
	</div>
	<div class="row">
		<div class="col-sm-6">
			<?php echo FormHelper::password('Senha', 'password', ['placeholder' => 'Digite sua senha']); ?>
		</div>
	</div>
	<?php echo FormHelper::submit('Enviar'); ?>		
</form>