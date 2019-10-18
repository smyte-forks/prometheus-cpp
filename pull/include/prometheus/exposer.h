#pragma once

#include <atomic>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "prometheus/collectable.h"
#include "prometheus/detail/pull_export.h"
#include "prometheus/registry.h"

class CivetServer;

namespace prometheus {

namespace detail {
class MetricsHandler;
}  // namespace detail

class PROMETHEUS_CPP_PULL_EXPORT Exposer {
 public:
  explicit Exposer(std::shared_ptr<CivetServer> server,
                   const std::string& uri = std::string("/metrics"));
  ~Exposer();
  void RegisterCollectable(const std::weak_ptr<Collectable>& collectable);

 private:
  std::shared_ptr<CivetServer> server_;
  std::vector<std::weak_ptr<Collectable>> collectables_;
  std::shared_ptr<Registry> exposer_registry_;
  std::unique_ptr<detail::MetricsHandler> metrics_handler_;
  std::string uri_;
};

}  // namespace prometheus
