\mainpage The Open Motion Planning Library

\htmlonly
<div class="row">
  <div class="col-sm-12">
  <div id="omplCarousel" class="carousel slide" data-ride="carousel">
    <!-- Indicators -->
    <ol class="carousel-indicators">
      <li data-target="#omplCarousel" data-slide-to="0" class="active"></li>
      <li data-target="#omplCarousel" data-slide-to="1"></li>
      <li data-target="#omplCarousel" data-slide-to="2"></li>
      <li data-target="#omplCarousel" data-slide-to="3"></li>
      <li data-target="#omplCarousel" data-slide-to="4"></li>
      <li data-target="#omplCarousel" data-slide-to="5"></li>
    </ol>
    <!-- Wrapper for slides -->
    <div class="carousel-inner">
      <div class="carousel-item active">
        <img src="images/frontpage/r2-iss-path.jpg">
        <div class="carousel-caption">
          <h4>OMPL used in ROS/MoveIt</h4>
          <p>OMPL is the default planning library in MoveIt and has been used for <a href="https://moveit.ros.org/robots">many robots</a>. Here, OMPL is used to plan footsteps for NASA's Robonaut2 aboard the International Space Station.</p>
        </div>
      </div>
      <div class="carousel-item">
        <img src="images/frontpage/Delft-APC2016.jpg">
        <div class="carousel-caption">
          <h4>Shelf Picking</h4>
          <p>In 2016 a <a href="https://www.tudelft.nl/en/3me/departments/cognitive-robotics-cor/people/robot-dynamics/">team from Delft University</a> won the Amazon Picking Challenge using OMPL in a tailored motion pipeline based on MoveIt.</p>
        </div>
      </div>
      <div class="carousel-item">
        <img src="images/frontpage/tmkit.jpg">
        <div class="carousel-caption">
          <h4>Task and Motion Planning</h4>
          <p>The Kavraki Lab has used OMPL for the low-level motion planning in <a href="http://tmkit.kavrakilab.org">TMKit</a>, a software package for combined task and motion planning.</p>
        </div>
      </div>
      <div class="carousel-item">
        <img src="images/frontpage/benchmarking.jpg">
        <div class="carousel-caption">
          <h4>Benchmarking</h4>
          <p>OMPL has extensive benchmarking capabilities. Benchmark results can be interactively explored on <a href="http://plannerarena.org">Planner Arena</a>.</p>
        </div>
      </div>
      <div class="carousel-item">
        <img src="images/frontpage/parallel_manipulator.jpg">
        <div class="carousel-caption">
          <h4>Constrained Motion Planning</h4>
          <p>OMPL supports planning for kinematically constrained robots. This parallel manipulator (included as a <a href="ConstrainedPlanningImplicitChain_8cpp_source.html">demo program</a>) has over 150 degrees of freedom, but feasible motions can still be computed in seconds.</p>
        </div>
      </div>
      <div class="carousel-item">
        <img src="images/frontpage/ompl-morse.jpg">
        <div class="carousel-caption">
          <h4>OMPL in MORSE</h4>
          <p>It is possible to use OMPL inside the <a href="http://www.openrobots.org/morse/doc/stable/morse.html">MORSE robot simulator</a>. This shows a robot car that, through planning, discovers a feasible trajectory to reach the target marked by the red X.</p>
        </div>
      </div>
    </div>
    <!-- Controls -->
    <a class="carousel-control-prev" href="#omplCarousel" role="button" data-slide="prev">
      <span class="carousel-control-prev-icon" aria-hidden="true"></span>
      <span class="sr-only">Previous</span> </a>
    <a class="carousel-control-next" href="#omplCarousel" role="button" data-slide="next">
      <span class="carousel-control-next-icon" aria-hidden="true"></span>
      <span class="sr-only">Next</span>
    </a>
  </div>
  </div>
</div>


<div class="row">
  <div class="col-sm-9">
    <div class="omplapp">
      <p>
        <b>OMPL</b>, the Open Motion Planning Library, consists of many state-of-the-art sampling-based motion planning
        algorithms. OMPL itself does not contain any code related to, e.g., collision checking or visualization. This is a
        deliberate design choice, so that OMPL is not tied to a particular collision checker or visualization front end.
        The library is designed so it can be easily integrated into
        <a href="integration.html">systems that provide the additional needed components</a>.
      </p>

      <p>
        <b>OMPL.app</b>, the front-end for <a href="/core">OMPL</a>, contains a lightweight wrapper for the
        <a href="https://github.com/flexible-collision-library/fcl">FCL</a> and
        <a href="http://gamma.cs.unc.edu/SSV">PQP</a> collision checkers and a simple GUI based on
        <a href="http://www.riverbankcomputing.co.uk/software/pyqt/intro">PyQt</a> /
        <a href="https://wiki.qt.io/Qt_for_Python">PySide</a>. The graphical front-end can be used for planning motions for rigid
        bodies and a few vehicle types (first-order and second-order cars, a blimp, and a quadrotor). It relies on the
        <a href="http://assimp.org">Assimp</a> library to import a large variety of mesh formats that can be used to
      represent the robot and its environment.
      </p>
    </div>
    <div class="ompl">
      <p>
        The Open Motion Planning Library (<b>OMPL</b>) consists of a set of sampling-based motion planning algorithms. The
        content of the library is limited to these algorithms, which means there is no environment specification, no
        collision detection or visualization. The library is designed so it can be easily integrated into
        <a href="integration.html">systems that provide the additional needed components</a>. For examples of complete systems
        using OMPL, see <a href="https://ompl.kavrakilab.org">OMPL.app</a> and <a href="https://moveit.ros.org">MoveIt</a>. We
        have also developed an <a href="education.html">educational module on motion planning</a> that is centered around
        OMPL.app. We are looking for educational partners to use and further develop the material. Please contact us for more
        information.
      </p>

      <p>
        OMPL is intended to be efficient, thread safe, easy to use, easily extensible and freely available (visit this
        project on <a href="https://github.com/ompl/ompl">Github</a>).
      </p>
    </div>
  </div>
  <div class="col-sm-3">
    <div class="row justify-content-around">
      <p><a href="download.html" class="btn btn-primary btn-sm">
        Download version&nbsp;1.6.0<br/>
        <small>Released: Feb 19, 2025</small>
      </a></p>

      <p><a href="citations.html" class="btn btn-primary btn-sm">
        Click for citation,<br><small>if you use OMPL in your work</small>
      </a></p>
    </div>
  </div>
</div>
<div class="row">
  <div class="col-lg-4 col-md-6">
    <h2>Library Contents</h2>
    <ul>
      <li>OMPL contains implementations of many sampling-based algorithms such as PRM, RRT, EST, SBL, KPIECE, SyCLOP,
        and several variants of these planners. See <a href="planners.html">available planners</a> for a complete list.</li>
      <li>All these planners operate on very abstractly defined state spaces. Many commonly used
        <a href="spaces.html">state spaces</a> are already implemented (e.g., SE(2), SE(3), R<sup>n</sup>, etc.).</li>
      <li>For any state space, different <a href="samplers.html">state samplers</a> can be used (e.g., uniform, Gaussian,
        obstacle-based, etc.).</li>
      <li><a href="api_overview.html">API overview</a>.</li>
      <li class="omplapp"><a href="/core">Documentation for just the OMPL core library (i.e., without the “app”
          layer)</a>.
      </li>
    </ul>
  </div>
  <div class="col-lg-4 col-md-6">
    <h2>Getting Started</h2>
    <ul>
      <li>The <a href="https://ompl.kavrakilab.org/OMPL_Primer.pdf">OMPL primer</a> provides a brief background on
        sampling-based motion planning, and an overview of OMPL.</li>
      <li><a href="download.html">Download</a> and <a href="installation.html">install</a> OMPL.</li>
      <li class="omplapp">Learn how to use the <a href="gui.html">OMPL.app GUI</a>.</li>
      <li><a href="group__demos.html">Demos</a> and <a href="tutorials.html">tutorials</a>.</li>
      <li><a href="FAQ.html">Frequently Asked Questions.</a></li>
      <li>Learn how to integrate your own code with <a href="buildSystem.html">OMPL's build system</a>.</li>
      <li><a href="integration.html">Learn more about how OMPL is integrated within other systems</a> (such as
        <a href="https://moveit.ros.org">MoveIt</a>, <a href="http://coppeliarobotics.com">V-REP</a>, <a
          href="http://openrave.org">OpenRAVE</a>, and
        <a href="https://www.openrobots.org/wiki/morse">MORSE</a>).</li>
      <li>If interested in using Python, make sure to read <a href="python.html">the documentation for the Python
          bindings</a>.</li>
    </ul>
  </div>
  <div class="col-lg-4 col-md-12">
    <h2>Other Resources</h2>
    <ul>
      <li><a href="education.html">OMPL for education.</a></li>
      <li><a href="gallery.html">Gallery of example uses of OMPL.</a></li>
      <li>If you use <a href="https://www.ros.org">ROS</a>, the recommended way to use OMPL is through <a
          href="https://moveit.ros.org">MoveIt</a>.</li>
      <li><a href="thirdparty.html">Third-party contributions.</a> (<a href="contrib.html">Contribute your own
          extensions!</a>)</li>
    </ul></div>
    <div class="col-lg-12 col-md-12">
      <h2>News &amp; Events</h2>
      <ul>
        <li><a href="https://vimeo.com/66567049">At ROSCON 2013, Sachin Chitta gave a presentation about MoveIt</a>, the new
          software framework for motion planning in ROS. It provides a common interface to motion planning libraries
          (including OMPL). The old ROS arm_navigation stack is now deprecated and all ROS users are encouraged to switch to
          MoveIt.</li>
        <li><a href="https://moveit.ros.org/wiki/Tutorials/ICRA2013">ICRA 2013 Tutorial on Motion Planning for Mobile
            Manipulation: State-of-the-art Methods and Tools</a>. Both OMPL and <a href="https://moveit.ros.org">MoveIt</a>
            were heavily featured in this tutorial.</li>
        <li><a href="http://ompl.kavrakilab.org/2012/12/05/ompl-wins-the-2012-oss-world-challenge-grand-prize.html">OMPL has won the 2012 Open Source Software World Grand
            Challenge!</a></li>
        <li><a href="ieee-ram-2012-ompl.pdf">An article about OMPL</a> has been accepted for publication in IEEE's Robotics
          &amp; Automation Magazine! It will appear in the December 2012 issue.</li>
        <li><a href="https://www.youtube.com/watch?v=r1zbuLc8RhI">At ROSCON 2012, Sachin Chitta and Ioan Șucan gave a talk
            about MoveIt</a>, the new motion planning stack in ROS. It provides a common interface to motion planning
          libraries in ROS (including OMPL). It will eventually replace the arm navigation stack.</li>
        <li><a href="http://kavrakilab.org/OMPLtutorial">IROS 2011 Tutorial on Motion Planning for Real Robots</a>. This
          hands-on tutorial described how to use the ROS and OMPL, but it also provided some background on sampling-based
          motion planning.</li>
      </ul>
    </div>
  </div>
</div>

\endhtmlonly
