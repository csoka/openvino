// Copyright (C) 2018-2025 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

// Plugin Config Engine

#pragma once

#include "intel_npu/config/config.hpp"

namespace intel_npu {

class PluginConfig final : public Config {
public:
    using EnableMap = std::unordered_map<std::string, bool>;

    explicit PluginConfig(const std::shared_ptr<const OptionsDesc>& desc) : Config(desc) {}

    void update(const ConfigMap& options, OptionMode mode = OptionMode::Both) override;

    bool hasOpt(std::string_view key) const;
    bool isOptPublic(std::string_view key) const;
    details::OptionConcept getOpt(std::string_view key) const;

    bool isAvailable(std::string key) const;
    void enable(std::string key, bool enable);
    void enableAll();
    void walkEnables(std::function<void(const std::string&)> cb) const;

    void addOrUpdateInternal(std::string key, std::string value);
    std::string getInternal(std::string key) const;
    std::string toStringForCompilerInternal() const;
    void walkInternals(std::function<void(const std::string&)> cb) const;

    // Returns a string with all config keys which have set values
    // and have OptionMode::Compile or OptionMode::Both
    std::string toStringForCompiler() const;

private:
    EnableMap _enabled;
    ConfigMap _internal_compiler_configs;
};

}  // namespace intel_npu
