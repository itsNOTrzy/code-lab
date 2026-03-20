 $(function(){
	  $(".dd").hover(function(){
			 $(".dd").stop().animate({
                width:'250px',
                height:'250px', 
				fontSize:'23px',
				
			 } );
			 $(".dd").css("border-radius","125px")
			 $(".dd").addClass("dd2");
		    
	  },function(){
	         $(".dd").stop().animate({
                width:'170px',
                height:'170px', 
				fontSize:'15px',
                borderRadius:'87',
			 } );
            
			 $(".dd").removeClass("dd2");
	  }
	  );
	 
	  
     $(".m").hover(function(){
			 $(".m1").animate({ opacity:'0'},1100,function(){
			    $(".m2").animate({ opacity:'0'},1100,function(){
				    $(".m3").animate({ opacity:'0'},1100);
				});
			 
			 });
		    
	  },function(){
	         $(".m1").stop().animate({ opacity:'1',},0);
			 $(".m2").stop().animate({ opacity:'1',},0);
			 $(".m3").stop().animate({ opacity:'1',},0);
           
	  }
	  );


});






























