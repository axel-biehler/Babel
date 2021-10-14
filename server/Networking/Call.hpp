#pragma once

namespace Babel {
    namespace Networking {
        class Call {
        public:
            Call(int from, int to);

            int getFrom() const;
            int getTo() const;

            bool operator==(const Call &other);

        private:
            int _from;
            int _to;
        };
    }
}


