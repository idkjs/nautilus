open ReactNative;
module Style = GoldStyle;
module Animated = GoldStyle.Animated;

type t = {
  forHeaderCenter: 'a. GoldStyle.Animated.value('a) => Style.t,
  forHeaderLeft: 'a. GoldStyle.Animated.value('a) => Style.t,
  forHeaderLeftLabel: 'a. GoldStyle.Animated.value('a) => Style.t,
  forHeaderLeftButton: 'a. GoldStyle.Animated.value('a) => Style.t,
  forHeaderRight: 'a. GoldStyle.Animated.value('a) => Style.t,
};

let crossFadeInterpolation = (~startRange, ~midRange, ~endRange, value) =>
  Animated.Value.interpolate(
    value,
    ~inputRange=[
      startRange,
      startRange +. 0.001,
      midRange -. 0.9,
      midRange -. 0.2,
      midRange,
      endRange -. 0.001,
      endRange,
    ],
    ~outputRange=`float([0.0, 0.0, 0.0, 0.3, 1.0, 0.0, 0.0]),
    (),
  );

let floating = {
  forHeaderCenter: value => {
    let offset = float_of_int(Dimensions.get(`window)##width / 2 - 70 + 25);
    GoldStyle.(
      style([
        opacity(
          GoldStyle.Animated(
            GoldStyle.Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.999), (-0.5), 0.0, 0.7, 0.999, 1.0],
              ~outputRange=`float([0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0]),
              (),
            ),
          ),
        ),
        Transform.makeAnimated(
          ~translateX=
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.99), 0.0, 0.99, 1.0],
              ~outputRange=
                `float([offset, offset, 0.0, -. offset, -. offset]),
              (),
            ),
          (),
        ),
      ])
    );
  },
  forHeaderLeft: _value => GoldStyle.style([]),
  forHeaderLeftButton: value =>
    Style.(
      style([
        opacity(
          Animated(
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.999), (-0.5), 0.0, 0.5, 0.999, 1.0],
              ~outputRange=`float([0.0, 0.0, 0.7, 1.0, 0.7, 0.0, 0.0]),
              (),
            ),
          ),
        ),
      ])
    ),
  forHeaderLeftLabel: value => {
    let offset = float_of_int(Dimensions.get(`window)##width / 2 - 70 + 25);
    Style.(
      style([
        opacity(
          Animated(
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.999), (-0.35), 0.0, 0.5, 0.999, 1.0],
              ~outputRange=`float([0.0, 0.0, 0.0, 1.0, 0.5, 0.0, 0.0]),
              (),
            ),
          ),
        ),
        Transform.makeAnimated(
          ~translateX=
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.999), 0.0, 0.999, 1.0],
              ~outputRange=
                `float([
                  offset,
                  offset,
                  0.0,
                  -. offset *. 1.5,
                  -. offset *. 1.5,
                ]),
              (),
            ),
          (),
        ),
      ])
    );
  },
  forHeaderRight: value =>
    Style.(
      style([
        opacity(
          Animated(
            value
            |> crossFadeInterpolation(
                 ~startRange=-1.0,
                 ~midRange=0.0,
                 ~endRange=1.0,
               ),
          ),
        ),
      ])
    ),
};
