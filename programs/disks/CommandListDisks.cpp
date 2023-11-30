#include "ICommand.h"
#include <Interpreters/Context.h>

namespace DB
{

namespace ErrorCodes
{
    extern const int BAD_ARGUMENTS;
}

class CommandListDisks final : public ICommand
{
public:
    CommandListDisks()
    {
        command_name = "list-disks";
        description = "List disks names";
        usage = "list-disks [OPTION]";
    }

    void processOptions(
        Poco::Util::LayeredConfiguration &,
        po::variables_map &) const override
    {}

    void execute(
        const std::vector<String> & command_arguments,
        std::shared_ptr<DiskSelector> &,
        Poco::Util::LayeredConfiguration & config) override
    {
        if (!command_arguments.empty())
        {
            printHelpMessage();
            throw DB::Exception(DB::ErrorCodes::BAD_ARGUMENTS, "Bad Arguments");
        }

        constexpr auto config_prefix = "storage_configuration.disks";
        constexpr auto default_disk_name = "default";

        Poco::Util::AbstractConfiguration::Keys keys;
        config.keys(config_prefix, keys);

        bool has_default_disk = false;

        for (const auto & disk_name : keys)
        {
            if (disk_name == default_disk_name)
                has_default_disk = true;
            std::cout << disk_name << '\n';
        }

        if (!has_default_disk)
            std::cout << default_disk_name << '\n';
    }
};
}

std::unique_ptr <DB::ICommand> makeCommandListDisks()
{
    return std::make_unique<DB::CommandListDisks>();
}
