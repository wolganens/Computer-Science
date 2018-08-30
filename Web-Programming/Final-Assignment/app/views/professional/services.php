<?php use App\Views\Helpers\FormHelper;  ?>
<h1 class="page-header">Meus Serviços</h1>

<div class="base">
	<div class="panel panel-default">
		<div class="panel-heading">
			Serviços
		</div>
		<div class="panel-body">
			<table class="table">
				<thead>
					<tr>
						<th>Categoria</th>
						<th>Cliente</th>
						<th>Endereço</th>
						<th>Status</th>
						<th>Preço</th>
					</tr>
				</thead>
				<tbody>
					<?php foreach ($services as $key => $service): ?>
						<tr>
							<td><?php echo $service->getCategory()->getName(); ?></td>
							<td><?php echo $service->getClient()->getName(); ?></td>
							<td><a class="show-map" data-toggle="modal" data-target="#map-modal" href="#map-modal"><?php echo $service->getAddress()->getAddressString(); ?></a></td>
							<td><?php echo $service->getStatus(); ?></td>
							<?php if (!$service->getPrice()): ?>
								<td>
									<form action="index.php?controller=Service&action=postUpdatePrice" class="form-inline" method="post">
										<input type="hidden" name="service" value="<?php echo $service->getId(); ?>">
										<?php echo FormHelper::text('', 'price', 0, null) ?><button class="btn btn-primary">Fazer orçamento</button>
									</form>
								</td>
							<?php else : ?>
								<td><?php echo $service->getPrice(); ?></td>
							<?php endif; ?>
						</tr>
					<?php endforeach; ?>
				</tbody>
			</table>
		</div>
	</div>
</div>
<script>
var geocoder;
var map;
function initialize() {
	geocoder = new google.maps.Geocoder();
	var latlng = new google.maps.LatLng(-34.397, 150.644);
	var mapOptions = {
		zoom: 18,
		center: latlng
	}
	map = new google.maps.Map(document.getElementById("map"), mapOptions);
}

</script>
<script async defer src="https://maps.googleapis.com/maps/api/js?key=AIzaSyAXlGtdggoAYD50SkbMU9CdzQNgXWIteNU&callback=initialize"
  type="text/javascript"></script>
<script>
function codeAddress(address_text) {
    var address = 'Brasil|Rio Grande do Sul|Alegrete|' + address_text;
    geocoder.geocode( { 'address': address}, function(results, status) {
      if (status == google.maps.GeocoderStatus.OK) {
        map.setCenter(results[0].geometry.location);
        var marker = new google.maps.Marker({
            map: map,
            position: results[0].geometry.location
        });
      } else {
        alert("Geocode was not successful for the following reason: " + status);
      }
    });
  }
</script>