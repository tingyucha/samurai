// Used in place of an external XML file

#ifndef SAMURAI_CONFIG_H
#define SAMURAI_CONFIG_H

#include <QString>

struct samurai_config {
  // operation
  int num_iterations;
  
  // radar
  int radar_skip;
  int radar_stride;
  int dynamic_stride;

  // c   <options>
  int spline_approximation;

  // COAMPS-TC array grid dimensions for current grid
  //  (could be either nest 1, 2 or )
  int nx;
  int ny;
  int nz;

  // grid
  float i_min;
  float i_max;
  float i_incr;
  float j_min;
  float j_max;
  float j_incr;
  float k_min;
  float k_max;
  float k_incr;

  // background
  float i_background_roi;
  float j_background_roi;

  // radar
  float i_reflectivity_roi;
  float j_reflectivity_roi;
  float k_reflectivity_roi;
  float dbz_pseudow_weight;
  float melting_zone_width;
  float mixed_phase_dbz;
  float rain_dbz;


  // parameters iter 1
  float bg_rhou_error;
  float bg_rhov_error;
  float bg_rhow_error;
  float bg_tempk_error;
  float bg_qv_error;
  float bg_rhoa_error;
  float bg_qr_error;
  float mc_weight;
  float i_filter_length;
  float j_filter_length;
  float k_filter_length;
  float i_spline_cutoff;
  float j_spline_cutoff;
  float k_spline_cutoff;
  float i_max_wavenumber;
  float j_max_wavenumber;
  float k_max_wavenumber;

  // observation errors
  float dropsonde_rhou_error;
  float dropsonde_rhov_error;
  float dropsonde_rhow_error;
  float dropsonde_tempk_error;
  float dropsonde_qv_error;
  float dropsonde_rhoa_error;
  float flightlevel_rhou_error;
  float flightlevel_rhov_error;
  float flightlevel_rhow_error;
  float flightlevel_tempk_error;
  float flightlevel_qv_error;
  float flightlevel_rhoa_error;
  float insitu_rhou_error;
  float insitu_rhov_error;
  float insitu_rhow_error;
  float insitu_tempk_error;
  float insitu_qv_error;
  float insitu_rhoa_error;
  float sfmr_windspeed_error;
  float qscat_rhou_error;
  float qscat_rhov_error;
  float ascat_rhou_error;
  float ascat_rhov_error;
  float amv_rhou_error;
  float amv_rhov_error;
  float lidar_sw_error;
  float lidar_power_error;
  float lidar_min_error;
  float radar_sw_error;
  float radar_fallspeed_error;
  float radar_min_error;

  // COAMPS-TC delta x and delta y for current grid
  float delx;
  float dely;

  // operation
  unsigned char load_background;
  unsigned char adjust_background;
  unsigned char preprocess_obs;
  unsigned char output_mish;
  unsigned char output_txt;
  unsigned char output_qc;
  unsigned char output_netcdf;
  unsigned char output_asi;
  unsigned char output_COAMPS;

  // boundary conditions
  char i_rhou_bcL[3];
  char i_rhou_bcR[3];
  char i_rhov_bcL[3];
  char i_rhov_bcR[3];
  char i_rhow_bcL[3];
  char i_rhow_bcR[3];
  char i_tempk_bcL[3];
  char i_tempk_bcR[3];
  char i_qv_bcL[3];
  char i_qv_bcR[3];
  char i_rhoa_bcL[3];
  char i_rhoa_bcR[3];
  char i_qr_bcL[3];
  char i_qr_bcR[3];
  char j_rhou_bcL[3];
  char j_rhou_bcR[3];
  char j_rhov_bcL[3];
  char j_rhov_bcR[3];
  char j_rhow_bcL[3];
  char j_rhow_bcR[3];
  char j_tempk_bcL[3];
  char j_tempk_bcR[3];
  char j_qv_bcL[3];
  char j_qv_bcR[3];
  char j_rhoa_bcL[3];
  char j_rhoa_bcR[3];
  char j_qr_bcL[3];
  char j_qr_bcR[3];
  char k_rhou_bcL[3];
  char k_rhou_bcR[3];
  char k_rhov_bcL[3];
  char k_rhov_bcR[3];
  char k_rhow_bcL[5];
  char k_rhow_bcR[5];
  char k_tempk_bcL[3];
  char k_tempk_bcR[3];
  char k_qv_bcL[3];
  char k_qv_bcR[3];
  char k_rhoa_bcL[3];
  char k_rhoa_bcR[3];
  char k_qr_bcL[3];
  char k_qr_bcR[3];

  // operation   
  char mode[4];
  
  // radar
  char qr_variable[4];
  char radar_dbz[4];
  char radar_vel[4];
  char radar_sw[4];

  // radar
  char mask_reflectivity[5];

  // background
  char ref_time[9];

  // background
  char ref_state[14];

  // operation
  char data_directory[128];
  char output_directory[128];

  // projection
  char projection[32];
};

// C API to the Samurai Driver3d

extern "C" {
  class VarDriver3D;

  // Constructor
  VarDriver3D *create_vardriver3D(const samurai_config *config);

  // Destructor
  void delete_vardriver3D(VarDriver3D *d);

  // Initializer that might alter some of the config
  int initialize_vardriver3D();

  // Run the analysis
  int run_vardriver3D(VarDriver3D *d,
		      // These are input values
		      int nx, int ny, int nsigma,
		      float dx, float dy,
		      float *sigmas,	// 2D array (nsigma)
		      float *latitude,	// 2D array (nx, ny)
		      float *longitude,	// 2D array
		      float *u1,	// 3D array (nx, ny, nsigma)  
		      float *v1,	// 3D array
		      float *w1,	// 3D array
		      float *th1,	// 3D array
		      float *p1,	// 3D array

		      // These are output values
		      float *usam,	// 3D array
		      float *vsam,	// 3D array
		      float *wsam,	// 3D array
		      float *thsam,	// 3D array
		      float *psam	// 3D array
		      );

  // debug stuff
  void dump_hash(QHash<QString, QString> &hash);
}

#endif /* SAMURAI_CONFIG_H */
