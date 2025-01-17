#pragma once

#include <ATen/record_function.h>
#include <map>
#include <mutex>
#include <set>
#include <string>

namespace torch {
namespace jit {
namespace mobile {

/* The BuildFeatureTracer class handles the attachment and removal of a
 * recording callback that traces the invocation of code that handles executing
 * generic build features.
 *
 * You can get the set of used build features using
 * getBuildFeatures().
 *
 * Note: This class is not thread safe or re-entrant, and should not be used
 * across multiple threads of execution.
 *
 */
struct BuildFeatureTracer final {
  at::CallbackHandle handle_;
  /* These are the custom class names (constant
   * character string) which shows up in code.
   */
  typedef std::set<std::string> build_feature_type;

  BuildFeatureTracer();
  static build_feature_type& getBuildFeatures();
  /* Protect concurrent writes into the set. */
  static std::mutex& getMutex();

  ~BuildFeatureTracer() {
    at::removeCallback(handle_);
  }
};

} // namespace mobile
} // namespace jit
} // namespace torch
