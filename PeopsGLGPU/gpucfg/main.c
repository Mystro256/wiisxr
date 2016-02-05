#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#ifdef ENABLE_NLS
#include <libintl.h>
#include <locale.h>
#endif

// Widgets
GtkWidget *window,
          *btnCancel,
          *btnSave,
          *spinXSize,
          *spinYSize,
          *chkKeepRatio,
		  *chkForceRatio43,
          *chkDithering,
          *chkFullScreen,
          *cbxTexQuality,
          *cbxTexFiltering,
          *cbxHiResTex,
          *spinVRam,
          *chkShowFPS,
          *chkUseFPSLimit,
          *vboxFPSLimit,
          *radFPSLimitAuto,
          *radFPSLimitManual,
          *spinFPSLimit,
          *chkUseFrameSkipping,
          *cbxOffscreen,
          *cbxFBTex,
          *cbxFBAccess,
          *chkMaskDetect,
          *chkOpaquePass,
          *chkAdvancedBlend,
          *chkScanLines,
          *spinScanLinesBlend,
          *chkFastMdec,
          *chk15bitMdec,
          *chkLineMode,
          *chkAntiAlias,
          *chkOGLExtensions,
          *chkScreenSmoothing,
		  *chkGteAccuracy,
          *chkUseGameFixes,
          *tblGameFixes,
          *chkCfgFix1,
          *chkCfgFix2,
          *chkCfgFix4,
          *chkCfgFix8,
          *chkCfgFix16,
          *chkCfgFix32,
          *chkCfgFix64,
          *chkCfgFix128,
          *chkCfgFix256,
          *chkCfgFix512,
          *chkCfgFix1024,
          *chkCfgFix2048,
          *chkCfgFix4096,
          *chkCfgFix8192,
          *chkCfgFix16384,
          *chkCfgFix32768,
          *chkCfgFix65536,
          *chkCfgFix131072,
          *btnFast,
          *btnBeautiful;

// Save values to the config file
void on_btnSave_clicked( GObject *object, gpointer user_data ) {
    FILE *out;
    out = fopen( "gpuPeopsMesaGL.cfg", "w+" );

    if ( out != NULL ) {

        // Computes the 'fixes' bitfield
        int cfgFixes = 0;
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix1      ) ) ) { cfgFixes |= (1 << 0); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix2      ) ) ) { cfgFixes |= (1 << 1); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix4      ) ) ) { cfgFixes |= (1 << 2); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix8      ) ) ) { cfgFixes |= (1 << 3); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix16     ) ) ) { cfgFixes |= (1 << 4); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix32     ) ) ) { cfgFixes |= (1 << 5); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix64     ) ) ) { cfgFixes |= (1 << 6); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix128    ) ) ) { cfgFixes |= (1 << 7); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix256    ) ) ) { cfgFixes |= (1 << 8); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix512    ) ) ) { cfgFixes |= (1 << 9); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix1024   ) ) ) { cfgFixes |= (1 << 10); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix2048   ) ) ) { cfgFixes |= (1 << 11); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix4096   ) ) ) { cfgFixes |= (1 << 12); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix8192   ) ) ) { cfgFixes |= (1 << 13); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix16384  ) ) ) { cfgFixes |= (1 << 14); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix32768  ) ) ) { cfgFixes |= (1 << 15); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix65536  ) ) ) { cfgFixes |= (1 << 16); }
        if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkCfgFix131072 ) ) ) { cfgFixes |= (1 << 17); }

        // Print data to the config file
        fprintf( out, "\nResX             = %i", gtk_spin_button_get_value_as_int( GTK_SPIN_BUTTON(   spinXSize           ) ) );
        fprintf( out, "\nResY             = %i", gtk_spin_button_get_value_as_int( GTK_SPIN_BUTTON(   spinYSize           ) ) );        
        fprintf( out, "\nKeepRatio        = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkKeepRatio        ) ) );
		fprintf( out, "\nForceRatio43     = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkForceRatio43     ) ) );
        fprintf( out, "\nDithering        = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkDithering        ) ) );
        fprintf( out, "\nFullScreen       = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkFullScreen       ) ) );
        fprintf( out, "\nTexQuality       = %i", gtk_combo_box_get_active(         GTK_COMBO_BOX(     cbxTexQuality       ) ) );
        fprintf( out, "\nTexFilter        = %i", gtk_combo_box_get_active(         GTK_COMBO_BOX(     cbxTexFiltering     ) ) );
        fprintf( out, "\nHiResTextures    = %i", gtk_combo_box_get_active(         GTK_COMBO_BOX(     cbxHiResTex         ) ) );
        fprintf( out, "\nVRamSize         = %i", gtk_spin_button_get_value_as_int( GTK_SPIN_BUTTON(   spinVRam            ) ) );        
        fprintf( out, "\nShowFPS          = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkShowFPS          ) ) );
        fprintf( out, "\nUseFrameLimit    = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkUseFPSLimit      ) ) );
        fprintf( out, "\nFPSDetection     = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( radFPSLimitAuto     ) ) );
        fprintf( out, "\nFrameRate        = %i", gtk_spin_button_get_value_as_int( GTK_SPIN_BUTTON(   spinFPSLimit        ) ) );
        fprintf( out, "\nUseFrameSkip     = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkUseFrameSkipping ) ) );
        fprintf( out, "\nOffscreenDrawing = %i", gtk_combo_box_get_active(         GTK_COMBO_BOX(     cbxOffscreen        ) ) );
        fprintf( out, "\nFrameTextures    = %i", gtk_combo_box_get_active(         GTK_COMBO_BOX(     cbxFBTex            ) ) );
        fprintf( out, "\nFrameAccess      = %i", gtk_combo_box_get_active(         GTK_COMBO_BOX(     cbxFBAccess         ) ) );
        fprintf( out, "\nMaskDetect       = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkMaskDetect       ) ) );
        fprintf( out, "\nOpaquePass       = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkOpaquePass       ) ) );
        fprintf( out, "\nAdvancedBlend    = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkAdvancedBlend    ) ) );
        fprintf( out, "\nScanLines        = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkScanLines        ) ) );
        fprintf( out, "\nScanLinesBlend   = %i", gtk_spin_button_get_value_as_int( GTK_SPIN_BUTTON(   spinScanLinesBlend  ) ) );
        fprintf( out, "\nFastMdec         = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkFastMdec         ) ) );
        fprintf( out, "\n15bitMdec        = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chk15bitMdec        ) ) );
        fprintf( out, "\nLineMode         = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkLineMode         ) ) );
        fprintf( out, "\nAntiAlias        = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkAntiAlias        ) ) );
        fprintf( out, "\nOGLExtensions    = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkOGLExtensions    ) ) );
        fprintf( out, "\nScreenSmoothing  = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkScreenSmoothing  ) ) );
        fprintf( out, "\nUseFixes         = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkUseGameFixes     ) ) );
        fprintf( out, "\nCfgFixes         = %i", cfgFixes );
		fprintf( out, "\nGteAccuracy      = %i", gtk_toggle_button_get_active(     GTK_TOGGLE_BUTTON( chkGteAccuracy      ) ) );

        fclose( out );
    }

    gtk_main_quit();
}

// Autoconfiguration callbacks

void on_btnFast_clicked( GObject *object, gpointer user_data ) {
    gtk_spin_button_set_value(    GTK_SPIN_BUTTON(   spinXSize ),           640 );
    gtk_spin_button_set_value(    GTK_SPIN_BUTTON(   spinYSize ),           480 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkKeepRatio ),          0 );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkForceRatio43 ),       0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkDithering ),          0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkFullScreen ),         0 );
    gtk_combo_box_set_active(     GTK_COMBO_BOX(     cbxTexQuality ),         0 );
    gtk_combo_box_set_active(     GTK_COMBO_BOX(     cbxTexFiltering ),       0 );
    gtk_combo_box_set_active(     GTK_COMBO_BOX(     cbxHiResTex ),           0 );
    gtk_spin_button_set_value(    GTK_SPIN_BUTTON(   spinVRam ),              0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkShowFPS ),            0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkUseFPSLimit ),        1 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( radFPSLimitAuto ),       1 );
    gtk_spin_button_set_value(    GTK_SPIN_BUTTON(   spinFPSLimit ),        200 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkUseFrameSkipping ),   0 );
    gtk_combo_box_set_active(     GTK_COMBO_BOX(     cbxOffscreen ),          1 );
    gtk_combo_box_set_active(     GTK_COMBO_BOX(     cbxFBTex ),              1 );
    gtk_combo_box_set_active(     GTK_COMBO_BOX(     cbxFBAccess ),           0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkMaskDetect ),         0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkOpaquePass ),         1 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkAdvancedBlend ),      0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkScanLines ),          0 );
    gtk_spin_button_set_value(    GTK_SPIN_BUTTON(   spinScanLinesBlend ),    0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkFastMdec ),           1 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chk15bitMdec ),          1 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkLineMode ),           0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkAntiAlias ),          0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkOGLExtensions ),      1 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkScreenSmoothing ),    0 );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkGteAccuracy ),        0 );
}

void on_btnBeautiful_clicked( GObject *object, gpointer user_data ) {
    gtk_spin_button_set_value(    GTK_SPIN_BUTTON(   spinXSize ),           640 );
    gtk_spin_button_set_value(    GTK_SPIN_BUTTON(   spinYSize ),           480 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkKeepRatio ),          0 );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkForceRatio43 ),       0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkDithering ),          0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkFullScreen ),         0 );
    gtk_combo_box_set_active(     GTK_COMBO_BOX(     cbxTexQuality ),         3 );
    gtk_combo_box_set_active(     GTK_COMBO_BOX(     cbxTexFiltering ),       0 );
    gtk_combo_box_set_active(     GTK_COMBO_BOX(     cbxHiResTex ),           0 );
    gtk_spin_button_set_value(    GTK_SPIN_BUTTON(   spinVRam ),              0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkShowFPS ),            0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkUseFPSLimit ),        1 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( radFPSLimitAuto ),       1 );
    gtk_spin_button_set_value(    GTK_SPIN_BUTTON(   spinFPSLimit ),        200 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkUseFrameSkipping ),   0 );
    gtk_combo_box_set_active(     GTK_COMBO_BOX(     cbxOffscreen ),          3 );
    gtk_combo_box_set_active(     GTK_COMBO_BOX(     cbxFBTex ),              2 );
    gtk_combo_box_set_active(     GTK_COMBO_BOX(     cbxFBAccess ),           0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkMaskDetect ),         1 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkOpaquePass ),         1 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkAdvancedBlend ),      1 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkScanLines ),          0 );
    gtk_spin_button_set_value(    GTK_SPIN_BUTTON(   spinScanLinesBlend ),    0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkFastMdec ),           0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chk15bitMdec ),          0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkLineMode ),           0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkAntiAlias ),          0 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkOGLExtensions ),      1 );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkScreenSmoothing ),    0 );   
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkGteAccuracy ),        0 );   
}

// Callbacks used to toggle the sensitivity of some parts of the GUI

void on_chkUseGameFixes_toggled( GObject *object, gpointer user_data ) {
    gtk_widget_set_sensitive( tblGameFixes, gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkUseGameFixes ) ) );
}

void on_chkUseFPSLimit_toggled( GObject *object, gpointer user_data ) {
    gtk_widget_set_sensitive( vboxFPSLimit, gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkUseFPSLimit ) ) );
}

void on_radFPSLimitManual_toggled( GObject *object, gpointer user_data ) {
    gtk_widget_set_sensitive( spinFPSLimit, gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( radFPSLimitManual ) ) );
}

void on_chkScanLines_toggled( GObject *object, gpointer user_data ) {
    gtk_widget_set_sensitive( spinScanLinesBlend, gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( chkScanLines ) ) );
}

/* Instanciates the GUI
   Reads the config file
   Sets widget states according to the config file
   Connect callbacks to signals */
int main( int argc, char **argv ) {
    GtkBuilder *builder;
    GError *error = NULL;
    FILE *in;
    char *pB, *p;
    int len, val;
    char t[256];

#ifdef ENABLE_NLS
    setlocale (LC_ALL, "");
    bindtextdomain (GETTEXT_PACKAGE, LOCALE_DIR);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);
#endif

    gtk_init( &argc, &argv );

	if (argc < 2) {
		printf ("Usage: cfgpeopsxgl {about | configure}\n");
		return 0;
	}

	if (strcmp(argv[1], "configure") != 0 && 
		strcmp(argv[1], "about") != 0) {
		printf ("Usage: cfgpeopsxgl {about | configure}\n");
		return 0;
	}
	
    builder = gtk_builder_new();

    // Load the glade file
    if ( !gtk_builder_add_from_file( builder, DATADIR "peopsxgl.ui", &error ) ) {
        g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
    }

    // Display the About dialog when the emulator ask for it
    if ( argv[1] && strcmp( argv[1], "about" ) == 0 ) {
        GtkWidget *widget;
        const char *authors[]= {"Adapted from P.E.Op.S OpenGL GPU by Pete Bernert", NULL};

        widget = gtk_about_dialog_new();
        gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(widget), "OpenGL GPU Driver");
        gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(widget), "1.18");
        gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(widget), authors);
        gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(widget), "http://pcsxr.codeplex.com/");

        gtk_dialog_run(GTK_DIALOG(widget));
        gtk_widget_destroy(widget);

        return 0;
    }
	else {
		// Get widgets from the glade file
		window              = GTK_WIDGET( gtk_builder_get_object( builder, "MainDialog"          ) );
		btnCancel           = GTK_WIDGET( gtk_builder_get_object( builder, "btnCancel"           ) );
		btnSave             = GTK_WIDGET( gtk_builder_get_object( builder, "btnSave"             ) );
		spinXSize           = GTK_WIDGET( gtk_builder_get_object( builder, "spinXSize"           ) );
		spinYSize           = GTK_WIDGET( gtk_builder_get_object( builder, "spinYSize"           ) );
		chkKeepRatio        = GTK_WIDGET( gtk_builder_get_object( builder, "chkKeepRatio"        ) );
		chkForceRatio43     = GTK_WIDGET( gtk_builder_get_object( builder, "chkForceRatio43"     ) );
		chkDithering        = GTK_WIDGET( gtk_builder_get_object( builder, "chkDithering"        ) );
		chkFullScreen       = GTK_WIDGET( gtk_builder_get_object( builder, "chkFullScreen"       ) );
		cbxTexQuality       = GTK_WIDGET( gtk_builder_get_object( builder, "cbxTexQuality"       ) );
		cbxTexFiltering     = GTK_WIDGET( gtk_builder_get_object( builder, "cbxTexFiltering"     ) );
		cbxHiResTex         = GTK_WIDGET( gtk_builder_get_object( builder, "cbxHiResTex"         ) );
		spinVRam            = GTK_WIDGET( gtk_builder_get_object( builder, "spinVRam"            ) );
		chkShowFPS          = GTK_WIDGET( gtk_builder_get_object( builder, "chkShowFPS"          ) );
		chkUseFPSLimit      = GTK_WIDGET( gtk_builder_get_object( builder, "chkUseFPSLimit"      ) );
		vboxFPSLimit        = GTK_WIDGET( gtk_builder_get_object( builder, "vboxFPSLimit"        ) );
		radFPSLimitAuto     = GTK_WIDGET( gtk_builder_get_object( builder, "radFPSLimitAuto"     ) );
		radFPSLimitManual   = GTK_WIDGET( gtk_builder_get_object( builder, "radFPSLimitManual"   ) );
		spinFPSLimit        = GTK_WIDGET( gtk_builder_get_object( builder, "spinFPSLimit"        ) );
		chkUseFrameSkipping = GTK_WIDGET( gtk_builder_get_object( builder, "chkUseFrameSkipping" ) );
		cbxOffscreen        = GTK_WIDGET( gtk_builder_get_object( builder, "cbxOffscreen"        ) );
		cbxFBTex            = GTK_WIDGET( gtk_builder_get_object( builder, "cbxFBTex"            ) );
		cbxFBAccess         = GTK_WIDGET( gtk_builder_get_object( builder, "cbxFBAccess"         ) );
		chkMaskDetect       = GTK_WIDGET( gtk_builder_get_object( builder, "chkMaskDetect"       ) );
		chkOpaquePass       = GTK_WIDGET( gtk_builder_get_object( builder, "chkOpaquePass"       ) );
		chkAdvancedBlend    = GTK_WIDGET( gtk_builder_get_object( builder, "chkAdvancedBlend"    ) );
		chkScanLines        = GTK_WIDGET( gtk_builder_get_object( builder, "chkScanLines"        ) );
		spinScanLinesBlend  = GTK_WIDGET( gtk_builder_get_object( builder, "spinScanLinesBlend"  ) );
		chkFastMdec         = GTK_WIDGET( gtk_builder_get_object( builder, "chkFastMdec"         ) );
		chk15bitMdec        = GTK_WIDGET( gtk_builder_get_object( builder, "chk15bitMdec"        ) );
		chkLineMode         = GTK_WIDGET( gtk_builder_get_object( builder, "chkLineMode"         ) );
		chkAntiAlias        = GTK_WIDGET( gtk_builder_get_object( builder, "chkAntiAlias"        ) );
		chkOGLExtensions    = GTK_WIDGET( gtk_builder_get_object( builder, "chkOGLExtensions"    ) );
		chkScreenSmoothing  = GTK_WIDGET( gtk_builder_get_object( builder, "chkScreenSmoothing"  ) );
		chkGteAccuracy      = GTK_WIDGET( gtk_builder_get_object( builder, "chkGteAccuracy"      ) );
		chkUseGameFixes     = GTK_WIDGET( gtk_builder_get_object( builder, "chkUseGameFixes"     ) );
		tblGameFixes        = GTK_WIDGET( gtk_builder_get_object( builder, "tblGameFixes"        ) );
		chkCfgFix1          = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix1"          ) );
		chkCfgFix2          = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix2"          ) );
		chkCfgFix4          = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix4"          ) );
		chkCfgFix8          = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix8"          ) );
		chkCfgFix16         = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix16"         ) );
		chkCfgFix32         = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix32"         ) );
		chkCfgFix64         = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix64"         ) );
		chkCfgFix128        = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix128"        ) );
		chkCfgFix256        = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix256"        ) );
		chkCfgFix512        = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix512"        ) );
		chkCfgFix1024       = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix1024"       ) );
		chkCfgFix2048       = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix2048"       ) );
		chkCfgFix4096       = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix4096"       ) );
		chkCfgFix8192       = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix8192"       ) );
		chkCfgFix16384      = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix16384"      ) );
		chkCfgFix32768      = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix32768"      ) );
		chkCfgFix65536      = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix65536"      ) );
		chkCfgFix131072     = GTK_WIDGET( gtk_builder_get_object( builder, "chkCfgFix131072"     ) );
		btnFast             = GTK_WIDGET( gtk_builder_get_object( builder, "btnFast"             ) );
		btnBeautiful        = GTK_WIDGET( gtk_builder_get_object( builder, "btnBeautiful"        ) );

		// Read the config file
		in = fopen( "gpuPeopsMesaGL.cfg", "rb" );
		if ( in ) {
			pB = (char *) malloc( 32767 );
			memset( pB, 0, 32767 );
			len = fread( pB, 1, 32767, in );
			fclose(in);
		}
		else pB = 0;

		val = 640;
		if ( pB ) {
			strcpy( t, "\nResX" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_spin_button_set_value( GTK_SPIN_BUTTON( spinXSize ), val );

		val = 480;
		if ( pB ) {
			strcpy( t, "\nResY" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_spin_button_set_value( GTK_SPIN_BUTTON( spinYSize ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nKeepRatio" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkKeepRatio ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nForceRatio43" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkForceRatio43 ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nDithering" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkDithering ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nFullScreen" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkFullScreen ), val );
		
		val = 0;
		if ( pB ) {
			strcpy( t, "\nTexQuality" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_combo_box_set_active( GTK_COMBO_BOX( cbxTexQuality ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nTexFilter" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_combo_box_set_active( GTK_COMBO_BOX( cbxTexFiltering ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nHiResTextures" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_combo_box_set_active( GTK_COMBO_BOX( cbxHiResTex ), val );

		val = 0;
		if ( pB ) {
			strcpy(t,"\nVRamSize");
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_spin_button_set_value( GTK_SPIN_BUTTON( spinVRam ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nShowFPS" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkShowFPS ), val );

		val = 1;
		if ( pB ) {
			strcpy( t, "\nUseFrameLimit" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkUseFPSLimit ), val );

		val = 1;
		if ( pB ) {
			strcpy( t, "\nFPSDetection" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( radFPSLimitAuto ), val );

		val = 200;
		if ( pB ) {
			strcpy(t,"\nFrameRate");
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_spin_button_set_value( GTK_SPIN_BUTTON( spinFPSLimit ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nUseFrameSkip" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkUseFrameSkipping ), val );

		val = 2;
		if ( pB ) {
			strcpy( t, "\nOffscreenDrawing" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_combo_box_set_active( GTK_COMBO_BOX( cbxOffscreen ), val );
		
		val = 1;
		if ( pB ) {
			strcpy( t, "\nFrameTextures" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_combo_box_set_active( GTK_COMBO_BOX( cbxFBTex ), val );
		
		val = 0;
		if ( pB ) {
			strcpy( t, "\nFrameAccess" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_combo_box_set_active( GTK_COMBO_BOX( cbxFBAccess ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nMaskDetect" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkMaskDetect ), val );

		val = 1;
		if ( pB ) {
			strcpy( t, "\nOpaquePass" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkOpaquePass ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nAdvancedBlend" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkAdvancedBlend ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nScanLines" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkScanLines ), val );

		val = 0;
		if ( pB ) {
			strcpy(t,"\nScanLinesBlend");
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_spin_button_set_value( GTK_SPIN_BUTTON( spinScanLinesBlend ), val );

		val = 1;
		if ( pB ) {
			strcpy( t, "\nFastMdec" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkFastMdec ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\n15bitMdec" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chk15bitMdec ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nLineMode" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkLineMode ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nAntiAlias" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkAntiAlias ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nOGLExtensions" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkOGLExtensions ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nScreenSmoothing" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkScreenSmoothing ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nGteAccuracy" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkGteAccuracy ), val );
		
		val = 0;
		if ( pB ) {
			strcpy( t, "\nUseFixes" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkUseGameFixes ), val );

		val = 0;
		if ( pB ) {
			strcpy( t, "\nCfgFixes" );
			p = strstr( pB, t );
			if ( p ) {
				p = strstr( p, "=" );
				len = 1;
				val = atoi( p + len );
			}
		}
		if ( val & (1 << 17) ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix131072 ), TRUE ); }
		if ( val & (1 << 16) ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix65536  ), TRUE ); }
		if ( val & (1 << 15) ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix32768  ), TRUE ); }
		if ( val & (1 << 14) ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix16384  ), TRUE ); }
		if ( val & (1 << 13) ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix8192   ), TRUE ); }
		if ( val & (1 << 12) ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix4096   ), TRUE ); }
		if ( val & (1 << 11) ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix2048   ), TRUE ); }
		if ( val & (1 << 10) ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix1024   ), TRUE ); }
		if ( val & (1 << 9)  ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix512    ), TRUE ); }
		if ( val & (1 << 8)  ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix256    ), TRUE ); }
		if ( val & (1 << 7)  ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix128    ), TRUE ); }
		if ( val & (1 << 6)  ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix64     ), TRUE ); }
		if ( val & (1 << 5)  ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix32     ), TRUE ); }
		if ( val & (1 << 4)  ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix16     ), TRUE ); }
		if ( val & (1 << 3)  ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix8      ), TRUE ); }
		if ( val & (1 << 2)  ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix4      ), TRUE ); }
		if ( val & (1 << 1)  ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix2      ), TRUE ); }
		if ( val & (1 << 0)  ) { gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( chkCfgFix1      ), TRUE ); }

		gtk_builder_connect_signals( builder, NULL );
		
		g_object_unref( G_OBJECT( builder ) );

		// Connect callbacks to signals
		g_signal_connect(G_OBJECT( window ),            "destroy", G_CALLBACK( gtk_main_quit ),                NULL );
		g_signal_connect(G_OBJECT( btnCancel ),         "clicked", G_CALLBACK( gtk_main_quit ),                NULL );
		g_signal_connect(G_OBJECT( btnSave ),           "clicked", G_CALLBACK( on_btnSave_clicked ),           NULL );
		g_signal_connect(G_OBJECT( chkUseGameFixes ),   "toggled", G_CALLBACK( on_chkUseGameFixes_toggled ),   NULL );
		g_signal_connect(G_OBJECT( chkUseFPSLimit ),    "toggled", G_CALLBACK( on_chkUseFPSLimit_toggled ),    NULL );
		g_signal_connect(G_OBJECT( radFPSLimitManual ), "toggled", G_CALLBACK( on_radFPSLimitManual_toggled ), NULL );
		g_signal_connect(G_OBJECT( chkScanLines ),      "toggled", G_CALLBACK( on_chkScanLines_toggled ),      NULL );
		g_signal_connect(G_OBJECT( btnFast ),           "clicked", G_CALLBACK( on_btnFast_clicked ),           NULL );
		g_signal_connect(G_OBJECT( btnBeautiful ),      "clicked", G_CALLBACK( on_btnBeautiful_clicked ),      NULL );

		// Call some callbacks to ensure widget state consistency
		on_chkUseGameFixes_toggled(   G_OBJECT( chkUseGameFixes   ), NULL );
		on_chkUseFPSLimit_toggled(    G_OBJECT( chkUseFPSLimit    ), NULL );
		on_radFPSLimitManual_toggled( G_OBJECT( radFPSLimitManual ), NULL );
		on_chkScanLines_toggled(      G_OBJECT( chkScanLines      ), NULL );

		gtk_widget_show( window );

		gtk_main();
	}
	
    return 0;
}
