$(document).ready(function () {

	$("img").on({
		"mouseover" : function() {
			this.src = 'images/room.jpg';
		},
		"mouseout" : function() {
			this.src='images/original.jpg';
		}
	});

});