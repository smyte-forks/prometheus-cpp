#include "prometheus/exposer.h"

#include <chrono>
#include <string>
#include <thread>

#include "prometheus/client_metric.h"

#include "CivetServer.h"
#include "handler.h"

namespace prometheus {

Exposer::Exposer(std::shared_ptr<CivetServer> server, const std::string& uri)
    : server_(server),
      exposer_registry_(std::make_shared<Registry>()),
      metrics_handler_(
          new detail::MetricsHandler{collectables_, *exposer_registry_}),
      uri_(uri) {
  RegisterCollectable(exposer_registry_);
  server_->addHandler(uri, metrics_handler_.get());
}

Exposer::~Exposer() { server_->removeHandler(uri_); }

void Exposer::RegisterCollectable(
    const std::weak_ptr<Collectable>& collectable) {
  collectables_.push_back(collectable);
}
}  // namespace prometheus
