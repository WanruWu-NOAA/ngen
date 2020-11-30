#ifndef NGEN_BMI_FORMULATION_H
#define NGEN_BMI_FORMULATION_H

#include <utility>
#include "Catchment_Formulation.hpp"

// Define the configuration parameter names used in the realization/formulation config JSON file
// First the required:
#define BMI_REALIZATION_CFG_PARAM_REQ__FORCING_FILE "forcing_file"
#define BMI_REALIZATION_CFG_PARAM_REQ__INIT_CONFIG "init_config"
#define BMI_REALIZATION_CFG_PARAM_REQ__MAIN_OUT_VAR "main_output_variable"
#define BMI_REALIZATION_CFG_PARAM_REQ__MODEL_TYPE "model_type_name"
#define BMI_REALIZATION_CFG_PARAM_REQ__USES_FORCINGS "uses_forcing_file"

// Then the optional
#define BMI_REALIZATION_CFG_PARAM_OPT__OTHER_IN_VARS "other_input_variables"
#define BMI_REALIZATION_CFG_PARAM_OPT__OUT_VARS "output_variables"
#define BMI_REALIZATION_CFG_PARAM_OPT__OUT_HEADER_FIELDS "output_header_fields"

namespace realization {

    /**
     * Abstraction of a formulation with a backing model object that implements the BMI.
     *
     * @tparam M The type for the backing BMI model object.
     */
    template <class M>
    class Bmi_Formulation : public Catchment_Formulation {

    public:

        /**
         * Minimal constructor for objects initialize using the Formulation_Manager and subsequent calls to
         * ``create_formulation``.
         *
         * @param id
         * @param forcing_config
         * @param output_stream
         */
        Bmi_Formulation(std::string id, forcing_params forcing_config, utils::StreamHandler output_stream)
                : Catchment_Formulation(std::move(id), std::move(forcing_config), output_stream) { };

        virtual ~Bmi_Formulation() {};

    protected:

        const string &get_bmi_init_config() const {
            return bmi_init_config;
        }

        const string &get_bmi_main_output_var() const {
            return bmi_main_output_var;
        }

        /**
         * Get the backing model object implementing the BMI.
         *
         * @return Shared pointer to the backing model object that implements the BMI.
         */
        std::shared_ptr<M> get_bmi_model() {
            return bmi_model;
        }

        const string &get_forcing_file_path() const {
            return forcing_file_path;
        }

        /**
         * Get the name of the specific type of the backing model object.
         *
         * @return The name of the backing model object's type.
         */
        std::string get_model_type_name() {
            return model_type_name;
        };

        /**
         * Get the values making up the header line from get_output_header_line(), but organized as a vector of strings.
         *
         * @return The values making up the header line from get_output_header_line() organized as a vector.
         */
        const vector<std::string> &get_output_header_fields() const {
            return output_header_fields;
        }

        /**
         * Get the names of variables in formulation output.
         *
         * Get the names of the variables to include in the output from this formulation, which should be some ordered
         * subset of the output variables from the model.
         *
         * @return
         */
        const vector<std::string> &get_output_variable_names() const {
            return output_variable_names;
        }

        bool is_bmi_uses_forcing_file() const {
            return bmi_uses_forcing_file;
        }

        /**
         * Test whether the backing model object has been initialize using the BMI standard ``Initialize`` function.
         *
         * @return Whether backing model object has been initialize using the BMI standard ``Initialize`` function.
         */
        virtual bool is_model_initialized() {
            return model_initialized;
        };

        void set_bmi_init_config(const string &init_config) {
            bmi_init_config = init_config;
        }

        void set_bmi_main_output_var(const string &main_output_var) {
            bmi_main_output_var = main_output_var;
        }

        /**
         * Set the backing model object implementing the BMI.
         *
         * @param model Shared pointer to the BMI model.
         */
        void set_bmi_model(std::shared_ptr<M> model) {
            bmi_model = model;
        }

        void set_bmi_uses_forcing_file(bool uses_forcing_file) {
            bmi_uses_forcing_file = uses_forcing_file;
        }

        void set_forcing_file_path(const string &forcing_path) {
            forcing_file_path = forcing_path;
        }

        /**
         * Set whether the backing model object has been initialize using the BMI standard ``Initialize`` function.
         *
         * @param is_initialized Whether model object has been initialize using the BMI standard ``Initialize``.
         */
        virtual void set_model_initialized(bool is_initialized) {
            model_initialized = is_initialized;
        }

        /**
         * Set the name of the specific type of the backing model object.
         *
         * @param type_name The name of the backing model object's type.
         */
        void set_model_type_name(std::string type_name) {
            model_type_name = std::move(type_name);
        }

        void set_output_header_fields(const vector<std::string> &output_headers) {
            output_header_fields = output_headers;
        }

        /**
         * Set the names of variables in formulation output.
         *
         * Set the names of the variables to include in the output from this formulation, which should be some ordered
         * subset of the output variables from the model.
         *
         * @param out_var_names the names of variables in formulation output, in the order they should appear.
         */
        void set_output_variable_names(const vector<std::string> &out_var_names) {
            output_variable_names = out_var_names;
        }

    private:
        std::string bmi_init_config;
        std::shared_ptr<M> bmi_model;
        std::string bmi_main_output_var;
        /** Whether the backing model uses/reads the forcing file directly for getting input data. */
        bool bmi_uses_forcing_file;
        std::string forcing_file_path;
        /**
         * Output header field strings corresponding to the variables output by the realization, as defined in
         * `output_variable_names`.
         */
        std::vector<std::string> output_header_fields;
        /**
         * Names of the variables to include in the output from this realization, which should be some ordered subset of
         * the output variables from the model.
         */
        std::vector<std::string> output_variable_names;
        bool model_initialized = false;
        std::string model_type_name;

        std::vector<std::string> OPTIONAL_PARAMETERS = {
                BMI_REALIZATION_CFG_PARAM_OPT__OTHER_IN_VARS,
                BMI_REALIZATION_CFG_PARAM_OPT__OUT_VARS,
                BMI_REALIZATION_CFG_PARAM_OPT__OUT_HEADER_FIELDS
        };
        std::vector<std::string> REQUIRED_PARAMETERS = {
                BMI_REALIZATION_CFG_PARAM_REQ__FORCING_FILE,
                BMI_REALIZATION_CFG_PARAM_REQ__INIT_CONFIG,
                BMI_REALIZATION_CFG_PARAM_REQ__MAIN_OUT_VAR,
                BMI_REALIZATION_CFG_PARAM_REQ__MODEL_TYPE,
                BMI_REALIZATION_CFG_PARAM_REQ__USES_FORCINGS
        };

    };

}

#endif //NGEN_BMI_FORMULATION_H