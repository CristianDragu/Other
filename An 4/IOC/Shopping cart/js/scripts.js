$( document ).ready(function() {

	function xml2json(xml, tab) {
	   	var X = {
	      toObj: function(xml) {
	         var o = {};
	         if (xml.nodeType==1) {   // element node ..
	            if (xml.attributes.length)   // element with attributes  ..
	               for (var i=0; i<xml.attributes.length; i++)
	                  o["@"+xml.attributes[i].nodeName] = (xml.attributes[i].nodeValue||"").toString();
	            if (xml.firstChild) { // element has child nodes ..
	               var textChild=0, cdataChild=0, hasElementChild=false;
	               for (var n=xml.firstChild; n; n=n.nextSibling) {
	                  if (n.nodeType==1) hasElementChild = true;
	                  else if (n.nodeType==3 && n.nodeValue.match(/[^ \f\n\r\t\v]/)) textChild++; // non-whitespace text
	                  else if (n.nodeType==4) cdataChild++; // cdata section node
	               }
	               if (hasElementChild) {
	                  if (textChild < 2 && cdataChild < 2) { // structured element with evtl. a single text or/and cdata node ..
	                     X.removeWhite(xml);
	                     for (var n=xml.firstChild; n; n=n.nextSibling) {
	                        if (n.nodeType == 3)  // text node
	                           o["#text"] = X.escape(n.nodeValue);
	                        else if (n.nodeType == 4)  // cdata node
	                           o["#cdata"] = X.escape(n.nodeValue);
	                        else if (o[n.nodeName]) {  // multiple occurence of element ..
	                           if (o[n.nodeName] instanceof Array)
	                              o[n.nodeName][o[n.nodeName].length] = X.toObj(n);
	                           else
	                              o[n.nodeName] = [o[n.nodeName], X.toObj(n)];
	                        }
	                        else  // first occurence of element..
	                           o[n.nodeName] = X.toObj(n);
	                     }
	                  }
	                  else { // mixed content
	                     if (!xml.attributes.length)
	                        o = X.escape(X.innerXml(xml));
	                     else
	                        o["#text"] = X.escape(X.innerXml(xml));
	                  }
	               }
	               else if (textChild) { // pure text
	                  if (!xml.attributes.length)
	                     o = X.escape(X.innerXml(xml));
	                  else
	                     o["#text"] = X.escape(X.innerXml(xml));
	               }
	               else if (cdataChild) { // cdata
	                  if (cdataChild > 1)
	                     o = X.escape(X.innerXml(xml));
	                  else
	                     for (var n=xml.firstChild; n; n=n.nextSibling)
	                        o["#cdata"] = X.escape(n.nodeValue);
	               }
	            }
	            if (!xml.attributes.length && !xml.firstChild) o = null;
	         }
	         else if (xml.nodeType==9) { // document.node
	            o = X.toObj(xml.documentElement);
	         }
	         else
	            alert("unhandled node type: " + xml.nodeType);
	         return o;
	      },
	      toJson: function(o, name, ind) {
	         var json = name ? ("\""+name+"\"") : "";
	         if (o instanceof Array) {
	            for (var i=0,n=o.length; i<n; i++)
	               o[i] = X.toJson(o[i], "", ind+"\t");
	            json += (name?":[":"[") + (o.length > 1 ? ("\n"+ind+"\t"+o.join(",\n"+ind+"\t")+"\n"+ind) : o.join("")) + "]";
	         }
	         else if (o == null)
	            json += (name&&":") + "null";
	         else if (typeof(o) == "object") {
	            var arr = [];
	            for (var m in o)
	               arr[arr.length] = X.toJson(o[m], m, ind+"\t");
	            json += (name?":{":"{") + (arr.length > 1 ? ("\n"+ind+"\t"+arr.join(",\n"+ind+"\t")+"\n"+ind) : arr.join("")) + "}";
	         }
	         else if (typeof(o) == "string")
	            json += (name&&":") + "\"" + o.toString() + "\"";
	         else
	            json += (name&&":") + o.toString();
	         return json;
	      },
	      innerXml: function(node) {
	         var s = ""
	         if ("innerHTML" in node)
	            s = node.innerHTML;
	         else {
	            var asXml = function(n) {
	               var s = "";
	               if (n.nodeType == 1) {
	                  s += "<" + n.nodeName;
	                  for (var i=0; i<n.attributes.length;i++)
	                     s += " " + n.attributes[i].nodeName + "=\"" + (n.attributes[i].nodeValue||"").toString() + "\"";
	                  if (n.firstChild) {
	                     s += ">";
	                     for (var c=n.firstChild; c; c=c.nextSibling)
	                        s += asXml(c);
	                     s += "</"+n.nodeName+">";
	                  }
	                  else
	                     s += "/>";
	               }
	               else if (n.nodeType == 3)
	                  s += n.nodeValue;
	               else if (n.nodeType == 4)
	                  s += "<![CDATA[" + n.nodeValue + "]]>";
	               return s;
	            };
	            for (var c=node.firstChild; c; c=c.nextSibling)
	               s += asXml(c);
	         }
	         return s;
	      },
	      escape: function(txt) {
	         return txt.replace(/[\\]/g, "\\\\")
	                   .replace(/[\"]/g, '\\"')
	                   .replace(/[\n]/g, '\\n')
	                   .replace(/[\r]/g, '\\r');
	      },
	      removeWhite: function(e) {
	         e.normalize();
	         for (var n = e.firstChild; n; ) {
	            if (n.nodeType == 3) {  // text node
	               if (!n.nodeValue.match(/[^ \f\n\r\t\v]/)) { // pure whitespace text node
	                  var nxt = n.nextSibling;
	                  e.removeChild(n);
	                  n = nxt;
	               }
	               else
	                  n = n.nextSibling;
	            }
	            else if (n.nodeType == 1) {  // element node
	               X.removeWhite(n);
	               n = n.nextSibling;
	            }
	            else                      // any other node
	               n = n.nextSibling;
	         }
	         return e;
	      }
	   };
	   if (xml.nodeType == 9) // document node
	      xml = xml.documentElement;
	   var json = X.toJson(X.toObj(X.removeWhite(xml)), xml.nodeName, "\t");
	   return "{\n" + tab + (tab ? json.replace(/\t/g, tab) : json.replace(/\t|\n/g, "")) + "\n}";
	}

	function parseXml(xml) {
		var dom = null;
		if (window.DOMParser) {
		  	try { 
		     	dom = (new DOMParser()).parseFromString(xml, "text/xml"); 
		  	} 
		  	catch (e) { dom = null; }
		}
		else if (window.ActiveXObject) {
		  	try {
		     	dom = new ActiveXObject('Microsoft.XMLDOM');
		     	dom.async = false;
		     	if (!dom.loadXML(xml))
					window.alert(dom.parseError.reason + dom.parseError.srcText);
		  	} 
		  	catch (e) { dom = null; }
		}
		else
		  	alert("cannot parse xml string!");
		return dom;
	}

	$('#cos').click(function(){
		$('#lista-ziare').toggle('slide');
    	$('#arata-cos').toggle('slide');
	});

	var papers = null;

	var rawFile = new XMLHttpRequest();
    rawFile.open("GET", 'ziare.xml', false);
    rawFile.onreadystatechange = function ()
    {
        if(rawFile.readyState === 4)
        {
            if(rawFile.status === 200 || rawFile.status == 0)
            {
                var allText = rawFile.responseText;
                papers = $.parseJSON(xml2json(parseXml(allText)).replace('undefined', ''));
            }
        }
    }
    rawFile.send();

    var publicatii = Array();
    papers['cifre-difuzare'].publicatii.publicatie.forEach(function(publicatie) {
    	if(parseInt(publicatie.cifre.total_vanzari, 10) > 10000) {
    		publicatie.pret = (Math.random() * 2 + 1).toString().match(/^-?\d+(?:\.\d{0,1})?/)[0]
    		publicatie.hasCD = (Math.floor(Math.random() * 2) == 1)
    		publicatie.cd = false
    		publicatii.push(publicatie);
    	}
    })
    var inCos = Array();
    var paginate = 0;

    getPapers();

    publicatii.forEach(function(publicatie) {
    	$('button[name="' + publicatie.nume + '"]').on('click', function() {
    		inCos.push(publicatie);
    		updateCos();
    		updateCosActions();
    		updateTotal()
    	});
    	$('input[name="' + publicatie.nume + '"]').on('click', function() {
    		publicatie.cd = !publicatie.cd
    	});
    })

    updateTotal()

    function getPapers() {
    	var publicatiiData = '';

    	for (i = 0; i < publicatii.length; i++) {
    		var publicatie = publicatii[i]
    		var publicatieData = '<tr>';
    		if( !(i >= paginate * 10 && i < Math.min(publicatii.length, (paginate + 1) * 10)) )
    			publicatieData = '<tr style="display: none">';

    		publicatieData += '<td>' + publicatie.nume + '</td>' +
    						  ((publicatie.hasCD)? '<td><input type="checkbox" name="' + publicatie.nume + '"></td>' : '<td></td>') +
    						  '<td>' + publicatie.pret + '</td>' +
    						  '<td style="width: 20px;"><button class="btn btn-primary" type="button" name="' + publicatie.nume + '">Add</button></td>';

    		publicatieData += '</tr>';

    		publicatiiData += publicatieData;
    	};

    	$('#body-lista-ziare').html(publicatiiData);
    }

    function updateCos() {
    	var ziareInCos = '';

    	inCos.forEach(function(ziar) {
    		var ziarInCos = '<tr>';

    		ziarInCos += '<td>' + ziar.nume + '</td>' +
						 ((ziar.hasCD)? '<td><input type="checkbox" name="' + ziar.nume + '-cos" ' + ((ziar.cd)? 'checked' : '') + '></td>' : '<td></td>') +
						 '<td>' + ((ziar.cd)? (parseFloat(ziar.pret) + 1) : ziar.pret) + '</td>' +
						 '<td style="width: 20px;"><a href="#" name="' + ziar.nume + '-remove"><span class="glyphicon glyphicon-remove"></span></a></td>';

			ziarInCos += '</tr>';

			ziareInCos += ziarInCos;
    	})

    	$("#body-arata-cos").html(ziareInCos);
    }

    function updateCosActions(){
		inCos.forEach(function(ziar) {
			$('a[name="' + ziar.nume + '-remove"]').on('click', function() {
				var index = inCos.indexOf(ziar);
				inCos.splice(index, 1);
				$("#body-arata-cos tr").eq(index).remove();
				updateTotal()
			});
			$('input[name="' + ziar.nume + '-cos"]').on('click', function() {
				var index = inCos.indexOf(ziar);
				ziar.cd = !ziar.cd
				$("#body-arata-cos tr").eq(index).children()[2].innerHTML = parseFloat(ziar.pret) + ((ziar.cd)? 1 : 0);
				updateTotal()
			})
		})
    }

    function updateTotal() {
    	var total = 0.0;
		
    	var obj = $("#body-arata-cos tr")

    	for (i = 0; i < obj.length; i++){
			total += parseFloat(obj[i].children[2].innerHTML)
    	}

		$("#suma").html('<h4><b>Total: ' + total + ' LEI</b></h4>');
    }

    $("#submit").on('click', function() {
    	inCos = []
    })

    $("#right-arrow").on('click', function() {
    	paginate = Math.min(paginate + 1, parseInt(publicatii.length / 10, 10))
    	for(i = 0; i < publicatii.length; i++){
    		$("#body-lista-ziare tr").eq(i).hide()
    	}
    	for (i = paginate * 10; i < Math.min(publicatii.length, (paginate + 1) * 10); i++) {
    		$("#body-lista-ziare tr").eq(i).show()
    	}
    })

    $("#left-arrow").on('click', function() {
    	paginate = Math.max(paginate - 1, 0)
    	for(i = 0; i < publicatii.length; i++){
    		$("#body-lista-ziare tr").eq(i).hide()
    	}
    	for (i = paginate * 10; i < Math.min(publicatii.length, (paginate + 1) * 10); i++) {
    		$("#body-lista-ziare tr").eq(i).show()
    	}
    })

})