/*****************************************************************************
 * Example code modified from Mapnik rundemo.cpp (r727, license LGPL).
 * Renders the State of California using USGS state boundaries data.
 *****************************************************************************/


#include <mapnik/map.hpp>
#include <mapnik/layer.hpp>
#include <mapnik/rule.hpp>
#include <mapnik/feature_type_style.hpp>
#include <mapnik/symbolizer.hpp>
#include <mapnik/text/placements/dummy.hpp>
#include <mapnik/text/text_properties.hpp>
#include <mapnik/text/formatting/text.hpp>
#include <mapnik/datasource_cache.hpp>
#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/agg_renderer.hpp>
#include <mapnik/expression.hpp>
#include <mapnik/color_factory.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/unicode.hpp>
#include <mapnik/save_map.hpp>
#include <mapnik/cairo_io.hpp>

#if defined(HAVE_CAIRO)
#include <mapnik/cairo/cairo_renderer.hpp>
#include <mapnik/cairo/cairo_image_util.hpp>
#endif

#include <iostream>

#include "demogData.h"
#include "parse.h"
#include "dataAQ.h"
#include "states.h"

std::vector<std::string> dataProjSetUp() {
    dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theData = read_csv(
            "./demo/490-MapLab7-STARTER/county_demographics.csv", DEMOG);


    std::vector<shared_ptr<psData>> thePoliceData = read_csvPolice(
            "./demo/490-MapLab7-STARTER/fatal-police-shootings-data-Q.csv", POLICE);

     //debug print out
    /*
    int i = 0;
    for (const auto &obj : theData) {
        //std::cout << *obj << std::endl;
        std::cout << " stateMap: " << obj->getState() << " " << theStatesAb[obj->getState()] << std::endl;
        i++;
        if (i > 2)
            break;
    }*/
     
    //cout << "number police incidents: " << thePoliceData.size() << endl;
    
    /* UNCOMMENT with your version of P2 theAnswers.createStateData(theData); */

    theAnswers.createStateData(theData);
    theAnswers.createStatePoliceData(thePoliceData);

    std::vector<std::string> theStates = theAnswers.reportTopShootingsPerCapita(); 
    /*
    std::vector<std::string> theStates = {"CA", "TX", "FL", "AZ", "GA", "CO", "OK", "OH", "TN", "NC", "AK", "HI", "ME", "MT"};
    return theStates;
    */

    return theStates;
}

int main ( int argc , char** argv)
{

    using namespace mapnik;

    std::vector<std::string> theStates = dataProjSetUp();
    std::vector<color> colorMap = {color(91, 80, 235),
    color(95, 245, 155),
    color(128, 235, 96),
    color(235, 235, 75),
    color(245, 213, 91),
    color(223, 170, 94),
    color(245, 134, 91),
    color(235, 91, 101) };

    const std::string srs_lcc="+proj=lcc +ellps=GRS80 +lat_0=49 +lon_0=-95 +lat+1=49 +lat_2=77 +datum=NAD83 +units=m +no_defs";
    const std::string srs_merc="+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0.0 +k=1.0 +units=m +nadgrids=@null +wktext +no_defs +over";


    try {
        std::cout << " creatin partial US map... \n";
        datasource_cache::instance().register_datasources("plugins/input/");
        freetype_engine::register_font("/fonts/dejavu-ttf-2.14/DejaVuSans.ttf");

        Map m(1200,800);
        m.set_background(parse_color("cadetblue"));
        //set projection
        m.set_srs(srs_merc);

        // create styles
        std::cout << "creating expression rules" << std::endl;
        std::string theStatesExp1, theStatesExp2, theStatesExp3;
        int count = round(theStates.size()/3.0);
        int i = 0;
        for (auto state : theStates) {
            if (i < count ) {
                theStatesExp1 += "[STUSPS] = " + state;
                if (i != count-1)
                    theStatesExp1 += " or ";
            } else if (i < count*2) {
                theStatesExp2 += "[STUSPS] = " + state;
                if (i != 2*count-1)
                    theStatesExp2 += " or ";
            } else {
                 theStatesExp3 += "[STUSPS] = " + state;
                if (i != 3*count-1 && i !=theStates.size()-1)
                    theStatesExp3 += " or ";
            }
            i++;
        }
        //DEBUG can remove
        std::cout << "the expression 1: " << theStatesExp1 << std::endl;
        std::cout << "the expression 2: " << theStatesExp2 << std::endl;
        std::cout << "the expression 3: " << theStatesExp3 << std::endl;

        std::cout << " creating styles ... \n";

        // States (polygon)
        feature_type_style topThird_style;
        {
            rule topThird_rule;
            topThird_rule.set_filter(parse_expression(theStatesExp1)); 
            {
                polygon_symbolizer poly_sym;
                put(poly_sym, keys::fill, color(235, 91, 101));
                topThird_rule.append(std::move(poly_sym));
            }
            topThird_style.add_rule(std::move(topThird_rule));
        }
        m.insert_style("topThird", std::move(topThird_style));

        feature_type_style midThird_style;
        {
            rule midThird_rule;
            midThird_rule.set_filter(parse_expression(theStatesExp2)); 
            {
                polygon_symbolizer poly_sym;
                put(poly_sym, keys::fill, color(245, 213, 91));
                midThird_rule.append(std::move(poly_sym));
            }
            midThird_style.add_rule(std::move(midThird_rule));
        }
        m.insert_style("midThird", std::move(midThird_style));

        feature_type_style botThird_style;
        {
            rule botThird_rule;
            botThird_rule.set_filter(parse_expression(theStatesExp3)); 
            {
                polygon_symbolizer poly_sym;
                put(poly_sym, keys::fill, color(91, 80, 235));
                botThird_rule.append(std::move(poly_sym));
            }
            botThird_style.add_rule(std::move(botThird_rule));
        }
        m.insert_style("botThird", std::move(botThird_style));


        std::cout << " added styles... \n";

        // State (polyline)
        feature_type_style statelines_style;
        {
            rule r;
            {
                line_symbolizer line_sym;
                put(line_sym,keys::stroke,color(0,0,0));
                put(line_sym,keys::stroke_width,1.0);
                put(line_sym,keys::stroke_linecap,ROUND_CAP);
                put(line_sym,keys::stroke_linejoin,ROUND_JOIN);
                r.append(std::move(line_sym));
            }
            statelines_style.add_rule(std::move(r));
        }
        m.insert_style("statelines", std::move(statelines_style));

       std::cout << " added 2nd style ... \n";

        // Layers
        // state data
        {
            parameters p;
            p["type"]="shape";
            p["file"]="demo/data/cb_2018_us_state_20m";
            p["encoding"]="utf8";

            layer lyr("DataProjMap");
            lyr.set_datasource(datasource_cache::instance().create(p));
            lyr.add_style("topThird");
            lyr.add_style("midThird");
            lyr.add_style("botThird");
            lyr.set_srs(srs_lcc);
     
            m.add_layer(lyr);
        }

        //state boundaries
        {
            parameters p;
            p["type"]="shape";
            p["file"]="demo/data/cb_2018_us_state_20m";
            p["encoding"]="utf8";

            layer lyr("StateLines");
            lyr.set_datasource(datasource_cache::instance().create(p));
            lyr.add_style("statelines");
            lyr.set_srs(srs_lcc);
     
            m.add_layer(lyr);
        }

        std::cout << "made layers" << std::endl;
        

        m.zoom_all();
        m.zoom(0.3);
        m.pan(-700, 400);

        image_rgba8 buf(m.width(),m.height());
        agg_renderer<image_rgba8> ren(m,buf);
        ren.apply();
        std::string msg("Writing out data for warm to cool coloring based on police shooting data:\n");
#ifdef HAVE_JPEG
        save_to_file(buf,"USMapPS.jpg","jpeg");
        msg += "- USMap.jpg\n";
#endif
                // save map definition (data + style)
        save_map(m, "map.xml");
    }
    catch ( std::exception const& ex )
    {
        std::cerr << "### std::exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch ( ... )
    {
        std::cerr << "### Unknown exception." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

