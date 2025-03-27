// index/api/update.js

export async function POST(req) {
  try {
    const url = process.env.KV_REST_API_URL;
    const token = process.env.KV_REST_API_TOKEN;
    const body = await req.json();

    if (!body || isNaN(body.flow) || isNaN(body.total)) {
      return new Response("Invalid payload", { status: 400 });
    }

    const payload = JSON.stringify({
      flow: parseFloat(body.flow),
      total: parseFloat(body.total),
    });

    // ✅ Changed from fuelData → latest
    const redisRes = await fetch(`${url}/set/latest`, {
      method: "POST",
      headers: {
        Authorization: `Bearer ${token}`,
        "Content-Type": "application/json",
      },
      body: JSON.stringify({
        value: payload,
      }),
    });

    if (!redisRes.ok) {
      console.error("Failed to store in Redis");
      return new Response("Storage failed", { status: 500 });
    }

    return new Response("Stored successfully", { status: 200 });
  } catch (err) {
    console.error("POST /api/update error:", err);
    return new Response("Error storing data", { status: 500 });
  }
}
