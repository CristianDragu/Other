$( document ).ready(function() {

	// GET the temperature using OpenWeatherMap for the local environment
	var weather = $.parseJSON($.ajax({
		async: false,
		type: "GET",
		dataType: "json",
		url: "http://api.openweathermap.org/data/2.5/weather?lat=45.145753&lon=26.812382&APPID=3e26ee3568e5271d3b4eb524d9c358b1",
	}).responseText);

	if (weather) {
		var time = new Date().toLocaleTimeString('en-US', { hour: "numeric", minute: "numeric"});
		$( "#weather-panel-title" ).text(weather.name + ", " + time);
		
		var umiditate = String(Math.floor(weather.main.humidity)) + "%";
		var temperatura = String(Math.floor(weather.main.temp - 273.15)) + " ℃";
		var descriere = weather.weather[0].description;

		$( "#humidity" ).text(umiditate);
		$( "#temperature" ).text(temperatura);
		$( "#info" ).text(descriere);
	}

	var rooms = getRooms();

	closeWindowsIfBadWeather();
	updateRoomsManager();

	// GET the rooms of the house
	function getRooms() {
		return $.parseJSON($.ajax({
	        type: "GET",
	        url: "http://localhost:8080/rooms",
	        data:{},
	        async: false,
	        dataType : 'json'
	    }).responseText);
	}

	function closeWindowsIfBadWeather(){
		var badWeather = ['rain', 'storm', 'snow', 'lightning', 'mist', 'fog'];
		for(let i of badWeather) {
			if (descriere.includes(i)) {
				$.ajax({
			        type: "POST",
			        url: "http://localhost:8080/close-windows",
			        data: {},
			        async: false,
			    });
				break;
			}
		}
	}

	// Updates the table which contains the rooms parameters
	function updateRoomsManager() {
		var roomsData = '';

	    rooms.forEach(function(room) {
	    	var roomData = '<tr>';
	    	
	    	roomData += '<td>' + room.name + '</td>' + 
	    				'<td>' + room.light + '</td>' + 
	    				'<td>' + room.windows + '</td>' +
	    				'<td>' + room.temperature + '</td>';

	    	roomData += '<td><a href="index.html" name="' + room.name + '-lights"><span class="glyphicon glyphicon-flash ' + ((room.light === 'ON')? 'blue' : 'grey') + '" aria-hidden="true"></span></a>&ensp;';
	    	roomData += '<a href="index.html" name="' + room.name + '-windows"><span class="glyphicon glyphicon-picture ' + ((room.windows === 'ON')? 'blue' : 'grey') + '" aria-hidden="true"></span></a></td>';
	    	roomData += '</tr>';

	    	roomsData += roomData;
	    });

	    $('#house-table-body').html(roomsData); 
	}

	function getGeolocation() {
		if (navigator.geolocation) {
		    navigator.geolocation.getCurrentPosition(showPosition);
		} else { 
		    console.log("Geolocation is not supported by this browser.");
		}
	}

	function showPosition(position) {
    	getWeatherByCoords(position.coords.latitude, position.coords.longitude);
	}

	function getWeatherByCoords(lat, lon){
		var weather = $.parseJSON($.ajax({
			async: false,
			type: "GET",
			dataType: "json",
			url: "http://api.openweathermap.org/data/2.5/weather?lat=" + lat + "&lon=" + lon + "&APPID=3e26ee3568e5271d3b4eb524d9c358b1",
		}).responseText);

		if (weather) {
			var time = new Date().toLocaleTimeString('en-US', { hour: "numeric", minute: "numeric"});
			$( "#weather-panel-title" ).text(weather.name + ", " + time);
			
			var umiditate = String(Math.floor(weather.main.humidity)) + "%";
			var temperatura = String(Math.floor(weather.main.temp - 273.15)) + " ℃";
			var descriere = weather.weather[0].description;

			$( "#humidity" ).text(umiditate);
			$( "#temperature" ).text(temperatura);
			$( "#info" ).text(descriere);

			initMap(lat, lon);
			closeWindowsIfBadWeather();
			updateRoomsManager();
		}
	}

	function getWeatherByCityName(city) {
		var weather = $.parseJSON($.ajax({
			async: false,
			type: "GET",
			dataType: "json",
			url: "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&APPID=3e26ee3568e5271d3b4eb524d9c358b1",
		}).responseText);

		if (weather) {
			var time = new Date().toLocaleTimeString('en-US', { hour: "numeric", minute: "numeric"});
			$( "#weather-panel-title" ).text(weather.name + ", " + time);
			
			var umiditate = String(Math.floor(weather.main.humidity)) + "%";
			var temperatura = String(Math.floor(weather.main.temp - 273.15)) + " ℃";
			var descriere = weather.weather[0].description;

			$( "#humidity" ).text(umiditate);
			$( "#temperature" ).text(temperatura);
			$( "#info" ).text(descriere);

			initMap(weather.coord.lat, weather.coord.lon);
			closeWindowsIfBadWeather();
			updateRoomsManager();
		}
	}

	$('input[name=city]').on('keypress', function (e) {
		if(e.which === 13){
			getWeatherByCityName($(this).val());
         	$(this).val("");
		}
	});

	$('a[name=current]').on('click', function() {
		getGeolocation();
	});

	rooms.forEach(function(room) {
		$('a[name=' + room.name +'-lights]').on('click', function() {
			$.ajax({
		        type: "POST",
		        url: "http://localhost:8080/switch-lights-room", 
		        data:{name: room.name},
		        async: false,
		    });
		    updateRoomsManager();
		});
		$('a[name=' + room.name +'-windows]').on('click', function() {
			$.ajax({
		        type: "POST",
		        url: (room.windows == 'ON')? "http://localhost:8080/close-windows-room" : "http://localhost:8080/open-windows-room", 
		        data:{name: room.name},
		        async: false,
		    });
		    closeWindowsIfBadWeather();
		    updateRoomsManager();
		});
	});
});

window.initMap = function (latitude = 45.145753, longitude = 26.812382) {
    map = new google.maps.Map(document.getElementById('map'), {
        center: {lat: latitude, lng: longitude},
        zoom: 18
    });
    var infowindow = new google.maps.InfoWindow();
    marker = new google.maps.Marker({
        position: new google.maps.LatLng(latitude, longitude),
        map: map
    });
    google.maps.event.addListener(marker, 'click', (function(marker) {
        return function() {
            infowindow.setContent("Your home");
            infowindow.open(map, marker);
        }
    })(marker));
}