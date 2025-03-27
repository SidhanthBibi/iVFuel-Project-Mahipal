import express from "express";
import cors from "cors";
import redis from "./redis.js";

const app = express();
app.use(cors());
app.use(express.json());

// POST /api/update
app.post("/api/update", async (req, res) => {
  const { flow, total } = req.body;
  if (flow == null || total == null) return res.status(400).json({ error: "Missing data" });

  await redis.set("flow", flow);
  await redis.set("total", total);
  res.status(200).json({ status: "saved" });
});

// GET /api/data
app.get("/api/data", async (req, res) => {
  const flow = await redis.get("flow");
  const total = await redis.get("total");

  res.json({
    flow: parseFloat(flow) || 0,
    total: parseFloat(total) || 0,
  });
});

export default app;
